import os
import cv2
import glob
import threading
import numpy as np

from PIL import Image
from logger import logger
from celery import Celery
from shutil import copyfile
from tqdm import tqdm, trange
from sklearn.model_selection import train_test_split

TRAIN_DATA_PATH = 'EKG'
LABEL_DATA_PATH = 'EKG_seg'
#  p_progress = tqdm(total=len(glob.glob('{}/*_json'.format(LABEL_DATA_PATH))))

def resize_img(directory):
    logger.info("Starting resize images")
    progress = tqdm(total=len(glob.glob(directory)))

    for path in glob.glob(directory):
        progress.update(1)

        idx = path.replace('{}/'.format(LABEL_DATA_PATH), '').replace('_json', '')
        o_img = Image.open("{}/img.png".format(path))
        l_img = Image.open("{}/label.png".format(path))

        w, h = o_img.size

        if (h, w) == (1050, 1488):
            ly, rx, ry = 324, 1488, 1023
        if (h, w) == (630, 892):
            ly, rx, ry = 194, 890, 614
        if (h, w) == (768, 1016):
            ly, rx, ry = 256, 1016, 768
        if (h, w) == (1001, 1328):
            ly, rx, ry = 324, 1328, 972

        o_cro = o_img.crop((0, ly, rx, ry))
        l_cro = l_img.crop((0, ly, rx, ry))

        o_cro.save("{}/resize_o.png".format(path))
        l_cro.save("{}/resize_l.png".format(path))

def convert_label(min_x, min_y, box_w, box_h, img_w, img_h):
    max_x = min_x + box_w
    max_y = min_y + box_h

    x = (min_x + (max_x-min_x)/2) * 1.0 / img_w
    y = (min_y + (max_y-min_y)/2) * 1.0 / img_h
    w = (max_x-min_x) * 1.0 / img_w
    h = (max_y-min_y) * 1.0 / img_h

    return x, y, w, h

def pre_process():
    # clean label data

    for path in glob.glob('label/*'):
        os.remove(path)
    
    threads = list()

    for path in glob.glob('{}/*_json'.format(LABEL_DATA_PATH)):
        threads.append(threading.Thread(target=pre_process_job, args=(path,)))
    
    for i in threads:
        i.start()
        i.join()

def pre_process_job(path):
    # deal label
    # type 0: qrs
    # type 1: p
    # type 2: t

    #  path = 'EKG_SEG/147_json'
    color_storage = {}

    original_img = cv2.imread('{}/resize_o.png'.format(path))
    label_img = cv2.imread('{}/resize_l.png'.format(path))
    erosion_img = cv2.erode(label_img, np.ones((10, 10), np.uint8), iterations=1)

    gray_img = cv2.cvtColor(erosion_img, cv2.COLOR_BGR2GRAY)
    th, binary = cv2.threshold(gray_img, 0, 255, cv2.THRESH_OTSU)
    contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    cv2.drawContours(erosion_img, contours, -1, (0, 0, 255), 3)

    bounding_boxes = [cv2.boundingRect(cnt) for cnt in contours]

    for bbox in bounding_boxes:
        [x, y, w, h] = bbox
        b, g, r = label_img[y+int(h/2), x+int(w/2)]
        cv2.rectangle(original_img, (x-10, y-10), (x+w+10, y+h+10), (255, 0, 0), 2)

        if (r, g, b) in color_storage:
            color_storage[(r, g, b)]+=1
        else:
            color_storage[(r, g, b)]=1

    cv2.imwrite('{}/remark.png'.format(path), original_img)

    # generate yolo label

    height, weight, c = original_img.shape
    YOLO_LABEL_INDEX = path.replace('EKG_seg/', '').replace('_json', '')

    for bbox in bounding_boxes:
        [x, y, w, h] = bbox
        _x, _y, _w, _h = convert_label(x, y, w, h, weight, height)
        b, g, r = label_img[y+int(h/2), x+int(w/2)]

        if len(color_storage)==1:
            _type = 0
        elif len(color_storage)==2:
            _type = 0 if (r, g, b)==(0, 128, 0) else 1
        else:
            if (r, g, b)==(0, 128, 0): _type = 0
            elif (r, g, b)==(128, 0, 0): _type = 1
            else: _type = 2

        copyfile('{}/{}_json/resize_o.png'.format(LABEL_DATA_PATH, YOLO_LABEL_INDEX), 'label/{}.png'.format(YOLO_LABEL_INDEX))

        with open("label/{}.txt".format(YOLO_LABEL_INDEX), 'a+') as f:
            f.write('{} {} {} {} {}\n'.format(_type, _x, _y, _w, _h))

    p_progress.update(1)

def split_data():
    temp = glob.glob('label/*.png')
    data_set = ['../' + x for x in temp]
    train_set, valid_set = train_test_split(data_set, test_size=0.2, random_state=10)

    with open('cfg/train.txt', 'w') as f:
        for data in train_set:
            f.write(data + '\n')

    with open('cfg/valid.txt', 'w') as f:
        for data in valid_set:
            f.write(data + '\n')

def test():
    # w    h    idx
    # 1050 1488 2_json
    # 630  892  210_json
    # 768  1016 113_json
    # 1001 1328 1_json
    
    HW_STORE = 'homework'
    total = len(glob.glob('EKG_seg/*_json'))
    meow = 1

    for path in glob.glob('EKG_seg/*_json'):
        # homework 1
        
        logger.info("{} [{}/{}]".format(path, meow, total))
        meow += 1

        img = Image.open('{}/img.png'.format(path))
        h, w = img.size
        index = path.replace('EKG_seg/', '').replace('_json', '')
        size_1_coordinate = [
                (117, 325), (435, 575), (435, 325), (748, 575), (748, 325), (1060, 575), (1060, 325), (1377, 575),
                (117, 500), (435, 724), (435, 500), (748, 724), (748, 500), (1060, 724), (1060, 500), (1377, 724),
                (117, 649), (435, 848), (435, 649), (748, 848), (748, 649), (1060, 848), (1060, 649), (1377, 848),
        ]
        size_2_coordinate = [
                (70, 196), (260, 344), (260, 196), (447, 344), (447, 196), (636, 344), (636, 196), (825, 344),
                (70, 299), (260, 419), (260, 299), (447, 419), (447, 299), (636, 419), (636, 299), (825, 419),
                (70, 389), (260, 509), (260, 389), (447, 509), (447, 389), (636, 509), (636, 389), (825, 509),
        ]
        size_3_coordinate = [
                (51, 255), (279, 383), (279, 255), (508, 383), (508, 255), (735, 383), (735, 255), (963, 383),
                (51, 346), (279, 507), (279, 346), (508, 507), (508, 346), (735, 507), (735, 346), (963, 507),
                (51, 456), (279, 617), (279, 456), (508, 617), (508, 456), (735, 617), (735, 456), (963, 617),
        ]
        size_4_coordinate = [
                (69, 195), (260, 299), (260, 195), (448, 299), (448, 195), (636, 299), (636, 195), (837, 299),
                (69, 299), (260, 403), (260, 299), (448, 403), (448, 299), (636, 403), (636, 299), (837, 403),
                (69, 403), (260, 480), (260, 403), (448, 480), (448, 403), (636, 480), (636, 403), (837, 480),
        ]
        
        if not os.path.exists('{}/1/{}_json'.format(HW_STORE, index)):
            os.makedirs("{}/1/{}_json".format(HW_STORE, index))
        
        if (w, h) == (1050, 1488):
            for i in range(1, 13):
                cro_img = img.crop((
                       size_1_coordinate[i*2-2][0],
                       size_1_coordinate[i*2-2][1],
                       size_1_coordinate[i*2-1][0],
                       size_1_coordinate[i*2-1][1]))
                cro_img.save('{}/1/{}_json/{}.png'.format(HW_STORE, index, i))
        
        if (w, h) == (630, 892):
            for i in range(1, 13):
                cro_img = img.crop((
                       size_2_coordinate[i*2-2][0],
                       size_2_coordinate[i*2-2][1],
                       size_2_coordinate[i*2-1][0],
                       size_2_coordinate[i*2-1][1]))
                cro_img.save('{}/1/{}_json/{}.png'.format(HW_STORE, index, i))

        if (w, h) == (768, 1016):
            for i in range(1, 13):
                cro_img = img.crop((
                       size_3_coordinate[i*2-2][0],
                       size_3_coordinate[i*2-2][1],
                       size_3_coordinate[i*2-1][0],
                       size_3_coordinate[i*2-1][1]))
                cro_img.save('{}/1/{}_json/{}.png'.format(HW_STORE, index, i))
        
        if (w, h) == (1001, 1328):
            for i in range(1, 13):
                cro_img = img.crop((
                       size_4_coordinate[i*2-2][0],
                       size_4_coordinate[i*2-2][1],
                       size_4_coordinate[i*2-1][0],
                       size_4_coordinate[i*2-1][1]))
                cro_img.save('{}/1/{}_json/{}.png'.format(HW_STORE, index, i))
        
        size_1_coordinate = [(141, 798, 1392, 998)]
        size_2_coordinate = [(69, 495, 820, 599)]
        size_3_coordinate = [(54, 585, 966, 707)]
        size_4_coordinate = [(0, 798, 1274, 948)]
        o_img = Image.open('{}/img.png'.format(path))
        l_img = Image.open("{}/label.png".format(path))
        
        if not os.path.exists('{}/3/{}_json'.format(HW_STORE, index)):
            os.makedirs("{}/3/{}_json".format(HW_STORE, index))

        if (w, h) == (1050, 1488):
            cro_o = o_img.crop(size_1_coordinate[0])
            cro_l = l_img.crop(size_1_coordinate[0])
            cro_l.save("{}/cro_l.png".format(path))

            label_img = cv2.imread("{}/cro_l.png".format(path))
            erosion_img = cv2.erode(label_img, np.ones((10, 10), np.uint8), iterations=1)

            gray_img = cv2.cvtColor(erosion_img, cv2.COLOR_BGR2GRAY)
            th, binary = cv2.threshold(gray_img, 0, 255, cv2.THRESH_OTSU)
            contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
            cv2.drawContours(erosion_img, contours, -1, (0, 0, 255), 3)

            bounding_boxes = [cv2.boundingRect(cnt) for cnt in contours]

            with open("{}/2/{}.txt".format(HW_STORE, index), 'w+') as f:
                f.write(str(len(bounding_boxes)))
            
            cnt = 1

            for bbox in bounding_boxes:
                [x, y, w, h] = bbox
                t_img = cro_o.crop((x, y, x+w, y+h))
                t_img.save("{}/3/{}_json/{}.png".format(HW_STORE, index, cnt))
                cnt += 1

        if (w, h) == (630, 892):
            cro_o = o_img.crop(size_2_coordinate[0])
            cro_l = l_img.crop(size_2_coordinate[0])
            cro_l.save("{}/cro_l.png".format(path))

            label_img = cv2.imread("{}/cro_l.png".format(path))
            erosion_img = cv2.erode(label_img, np.ones((10, 10), np.uint8), iterations=1)

            gray_img = cv2.cvtColor(erosion_img, cv2.COLOR_BGR2GRAY)
            th, binary = cv2.threshold(gray_img, 0, 255, cv2.THRESH_OTSU)
            contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
            cv2.drawContours(erosion_img, contours, -1, (0, 0, 255), 3)

            bounding_boxes = [cv2.boundingRect(cnt) for cnt in contours]

            with open("{}/2/{}.txt".format(HW_STORE, index), 'w+') as f:
                f.write(str(len(bounding_boxes)))
            
            cnt = 1

            for bbox in bounding_boxes:
                [x, y, w, h] = bbox
                t_img = cro_o.crop((x, y, x+w, y+h))
                t_img.save("{}/3/{}_json/{}.png".format(HW_STORE, index, cnt))
                cnt += 1

        if (w, h) == (768, 1016):
            cro_o = o_img.crop(size_3_coordinate[0])
            cro_l = l_img.crop(size_3_coordinate[0])
            cro_l.save("{}/cro_l.png".format(path))

            label_img = cv2.imread("{}/cro_l.png".format(path))
            erosion_img = cv2.erode(label_img, np.ones((10, 10), np.uint8), iterations=1)

            gray_img = cv2.cvtColor(erosion_img, cv2.COLOR_BGR2GRAY)
            th, binary = cv2.threshold(gray_img, 0, 255, cv2.THRESH_OTSU)
            contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
            cv2.drawContours(erosion_img, contours, -1, (0, 0, 255), 3)

            bounding_boxes = [cv2.boundingRect(cnt) for cnt in contours]

            with open("{}/2/{}.txt".format(HW_STORE, index), 'w+') as f:
                f.write(str(len(bounding_boxes)))
            
            cnt = 1

            for bbox in bounding_boxes:
                [x, y, w, h] = bbox
                t_img = cro_o.crop((x, y, x+w, y+h))
                t_img.save("{}/3/{}_json/{}.png".format(HW_STORE, index, cnt))
                cnt += 1

        if (w, h) == (1001, 1328):
            cro_o = o_img.crop(size_4_coordinate[0])
            cro_l = l_img.crop(size_4_coordinate[0])
            cro_l.save("{}/cro_l.png".format(path))

            label_img = cv2.imread("{}/cro_l.png".format(path))
            erosion_img = cv2.erode(label_img, np.ones((10, 10), np.uint8), iterations=1)

            gray_img = cv2.cvtColor(erosion_img, cv2.COLOR_BGR2GRAY)
            th, binary = cv2.threshold(gray_img, 0, 255, cv2.THRESH_OTSU)
            contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
            cv2.drawContours(erosion_img, contours, -1, (0, 0, 255), 3)

            bounding_boxes = [cv2.boundingRect(cnt) for cnt in contours]

            with open("{}/2/{}.txt".format(HW_STORE, index), 'w+') as f:
                f.write(str(len(bounding_boxes)))
            
            cnt = 1

            for bbox in bounding_boxes:
                [x, y, w, h] = bbox
                t_img = cro_o.crop((x, y, x+w, y+h))
                t_img.save("{}/3/{}_json/{}.png".format(HW_STORE, index, cnt))
                cnt += 1

if __name__ == '__main__':
    #  resize_img('EKG_seg/*_json')
    #  pre_passignmentsrocess()
    #  split_data()
    test()

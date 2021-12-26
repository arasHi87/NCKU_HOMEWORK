import cv2
import matplotlib.pyplot as plt
from tensorflow.keras.applications.resnet50 import ResNet50
from tensorflow.keras.layers import Dense, Dropout, Flatten
from tensorflow.keras.models import Model
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.preprocessing.image import ImageDataGenerator


class Train:
    def __init__(self):
        self.data = "data"
        self.IMAGE_SIZE = (224, 224)
        self.NUM_CLASSES = 2
        self.BATCH_SIZE = 16
        self.EPOCH = 10
        self.FREEZE_LAYERS = 2
        self.CHECKPOINT_PATH = 'data/checkpoint.hdf5'
        self.RESIZE_CHECKPOINT_PATH = 'data/resize_checkpoint.hdf5'
        self.DATASETS_PATH = 'data/dataset'
        self.LOG_PATH = 'data/log'
        self.RESIZE_LOG_PATH = 'data/resize_log'

    def _load_data(self):
        trainData = ImageDataGenerator(
            rotation_range=40,
            width_shift_range=0.2,
            height_shift_range=0.2,
            shear_range=0.2,
            zoom_range=0.2,
            channel_shift_range=10,
            horizontal_flip=True,
            fill_mode='nearest',
            validation_split=0.2
        )
        trainBatch = trainData.flow_from_directory(
            self.DATASETS_PATH,
            target_size=self.IMAGE_SIZE,
            interpolation='bicubic',
            class_mode='categorical',
            shuffle=True,
            batch_size=self.BATCH_SIZE,
            subset='training'
        )
        validateBatch = trainData.flow_from_directory(
            self.DATASETS_PATH,
            target_size=self.IMAGE_SIZE,
            interpolation='bicubic',
            class_mode='categorical',
            shuffle=True,
            batch_size=self.BATCH_SIZE,
            subset='validation'
        )

    def show_model(self):
        self._load_data()
        net = ResNet50(
            include_top=False,
            weights='imagenet',
            input_tensor=None,
            input_shape=(self.IMAGE_SIZE[0], self.IMAGE_SIZE[1], 3)
        )
        x = net.output
        x = Flatten()(x)
        x = Dropout(0.5)(x)

        outputLayer = Dense(self.NUM_CLASSES, activation='softmax', name='softmax')(x)
        net = Model(inputs=net.input, outputs=outputLayer)
        net.compile(optimizer=Adam(lr=1e-5), loss='categorical_crossentropy', metrics=['accuracy'])
        net.summary()

    def show_board(self):
        img = plt.imread(f"data/board.png")
        plt.axis("off")
        plt.imshow(img)
        plt.show()
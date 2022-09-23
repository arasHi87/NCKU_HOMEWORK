import regex as re

targets = re.findall(u"[\u4e00-\u9fff]+|[a-zA-Z0-9]+|[，、。？！]", input())
words, result = set(), list()

if __name__ == "__main__":
    with open("dict_no_space.txt", "r", encoding="utf8") as fp:
        lines = fp.readlines()
        words.update(line.strip() for line in lines)
    for target in targets:
        if not re.search(u"[\u4e00-\u9fff]", target):
            result.append(target)
        else:
            buffer, i, tmp = "", 0, 0
            while i < len(target):
                tmp = i + 1
                for j in range(i + 1, len(target) + 1):
                    if target[i:j] in words:
                        buffer, tmp = target[i:j], j
                i = tmp
                result.append(buffer)
    print(result)

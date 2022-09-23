# from pprint import pprint

from typing import List

import regex as re
import requests

position = []
URL = "http://140.116.245.157:2001"
TOKEN = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzUxMiJ9.eyJ2ZXIiOjAuMSwiaWF0IjoxNjYzMzA1NjgzLCJ1c2VyX2lkIjoiNDQxIiwiaWQiOjUwMSwi\
c2NvcGVzIjoiMCIsInN1YiI6IiIsImlzcyI6IkpXVCIsInNlcnZpY2VfaWQiOiIxIiwiYXVkIjoid21ta3MuY3NpZS5lZHUudHciLCJuYmYiOjE2NjMzMD\
U2ODMsImV4cCI6MTY3ODg1NzY4M30.sBw0g957OsLJzt0Hzd3OpxeaZEdDPgguRp11-D71_LL8TO9xD4xD6ftaw28-e4rA9SdP_kh617FVcDXw8AKSChio\
mB-p5e8ivWkdyuXrUdPiXaaksMuSifjuTrFgsNG3DhCDRdELaQISdB11KiaweBbcrto3IwN6_nOprJs-_0o"


def get_ws(pos_s: int, pos_e: int, ws: List[str]) -> str:
    # pos_s: position start
    # pos_e: pos_end
    ret = ""
    for idx in range(len(position)):
        pos = position[idx]
        if (pos_s, pos_e) == pos:
            return ws[idx]
        if pos_s <= pos[0]:
            ret += ws[idx]
        if pos_e == pos[1]:
            return ret
    return ""


def parse(string: str, pattern: str, name: str, ws: List[str]) -> None:
    for match in re.finditer(pattern, string):
        print(get_ws(match.span()[0], match.span()[1], ws), name)


if __name__ == "__main__":
    data = "美國參議院針對今天總統布什所提名的勞工部長趙小蘭展開認可聽證會，預料她將會很順利通過參議院支持，成為該國有史以來第一位的華裔女性內閣成員。"
    req = requests.post(URL, data={"data": data, "token": TOKEN})
    resp = req.json()

    string = ""
    for idx in range(len(resp["pos"][0])):
        pos, ws = resp["pos"][0][idx], resp["ws"][0][idx]
        position.append((len(string), len(string) + len(pos)))
        string += pos

    targets = [
        (r"Nb", "people"),
        (r"(VC)+(Na)+", "event"),
        (r"Nd", "time"),
        (r"(Nc)+", "location"),
        (r"(Na)+", "object"),
    ]
    for target in targets:
        parse(string, target[0], target[1], resp["ws"][0])

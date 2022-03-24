# -*- coding: utf-8 -*-

import requests
import json
from bs4 import BeautifulSoup
from operator import itemgetter
from collections import defaultdict

url = 'https://kenkoooo.com/atcoder/resources/lang.json'
headers = {'content-type': 'application/json'}

r = requests.get(url, headers=headers)
data = r.json()

users = defaultdict(dict)
for d in data:
    # ユーザー毎、言語毎のAC数をまとめる
    users[d['user_id']][d['language']] = d['count']

res = {}
for username, langs in users.items():
    # AC数の多い言語から並べる
    li = sorted(langs.items(), key=itemgetter(1), reverse=True)
    lang, count = li[0]
    # AC数が1番多い言語がPythonかPyPy
    # if lang == 'Python' or lang == 'PyPy':
    #     res[username] = [lang, count]
    # C++かJava以外
    if lang != 'C++' and lang != 'Java':
        res[username] = [lang, count]


i = ranking = 1
while True:
    r = requests.get('https://atcoder.jp/ranking/all?page={0}'.format(i))
    soup = BeautifulSoup(r.content, "html.parser")
    # <a class="username">
    a_tags = soup.find_all('a', class_='username')
    # 茶色以降はbreak
    if a_tags[0].span.get('class')[0] == 'user-brown':
        break
    for a in a_tags:
        username = a.text
        # AC数リストに載っているユーザーなら、レーティング情報を追加する
        if username in res:
            rating = a.parent.next_sibling.next_sibling.next_sibling.next_sibling.text
            country = a.previous_sibling.previous_sibling['href'][-2:]
            print('username: {0}, country: {1}, lang: {2}, count: {3}, rating: {4}, ranking: {5}'.format(
                username, country, res[username][0], res[username][1], rating, ranking))
            ranking += 1
        # とりあえず自分まででいいや
        if username == 'Coki628':
            exit()
    # とりあえず500位まで
    if ranking > 500: break
    print('rating page {0}, done'.format(i))
    i += 1

# -*- coding: utf-8 -*-

import requests
import json
from bs4 import BeautifulSoup
from operator import itemgetter
from collections import defaultdict

url = 'https://kenkoooo.com/atcoder/resources/ac.json'
# url = 'https://kenkoooo.com/atcoder/resources/lang.json'
headers = {'content-type': 'application/json'}

r = requests.get(url, headers=headers)
data = r.json()

res = []
for d in data:
    user = (d['user_id'], d['problem_count'])
    res.append(user)
res.sort(key=itemgetter(1), reverse=True)

# AC数ランキングトップxx
border = 50
users = {}
for i, user in enumerate(res[:border]):
    id, count = user
    users[id] = (i+1, count)

i = ranking = 1
while True:
    r = requests.get('https://atcoder.jp/ranking?page={0}'.format(i))
    soup = BeautifulSoup(r.content, "html.parser")
    # <a class="username">
    a_tags = soup.find_all('a', class_='username')
    # 茶色以降はbreak
    if a_tags[0].span.get('class')[0] == 'user-brown':
        break
    for a in a_tags:
        username = a.text
        # AC数リストに載っているユーザーなら、レーティング情報を追加する
        if username in users:
            _ranking = a.parent.previous_sibling.previous_sibling.text
            rating = a.parent.next_sibling.next_sibling.next_sibling.next_sibling.text
            # 冠の人はDom位置変わるから
            if int(_ranking) <= 100:
                country = a.previous_sibling.previous_sibling.previous_sibling.previous_sibling['href'][-2:]
            else:
                country = a.previous_sibling.previous_sibling['href'][-2:]
            print('username: {0}, country: {1}, count: {2}, rating: {3}, ranking: {4}, ac-ranking: {5}'.format(
                username, country, users[username][1], rating, ranking, users[username][0]))
            ranking += 1
        # # とりあえず自分まででいいや
        # if username == 'Coki628':
        #     exit()
    # xx位まで全員見たら終了
    if ranking > border: break
    print('rating page {0}, done'.format(i))
    i += 1

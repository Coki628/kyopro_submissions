# -*- coding: utf-8 -*-

import requests
import json
from operator import itemgetter

url = 'https://kenkoooo.com/atcoder/resources/lang.json'
headers = {'content-type': 'application/json'}

r = requests.get(url, headers=headers)
data = r.json()

res = []
for d in data:
    user = (d['user_id'], d['count'], d['language'])
    res.append(user)
res.sort(key=itemgetter(1), reverse=True)

# 言語別AC数ランキングトップ100
for i, user in enumerate(res[:100]):
    id, count, lang = user
    print(i+1, id, count, lang)

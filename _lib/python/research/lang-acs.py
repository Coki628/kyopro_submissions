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
    if d['language'] == 'Python':
        user = (d['user_id'], d['count'])
        res.append(user)
res.sort(key=itemgetter(1), reverse=True)

# メイン言語がpythonでのAC数ランキング
for i, user in enumerate(res[:20]):
    id, count = user
    print(i+1, id, count)

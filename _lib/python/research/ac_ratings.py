import requests
from bs4 import BeautifulSoup
from operator import itemgetter

limit = 100
url = 'https://kenkoooo.com/atcoder/atcoder-api/v3/ac_ranking?from=0&to={0}'.format(limit)
headers = {'content-type': 'application/json'}

r = requests.get(url, headers=headers)
data = r.json()

res = []
for d in data:
    url = 'https://atcoder.jp/users/' + d['user_id']
    r = requests.get(url)
    soup = BeautifulSoup(r.content, "html.parser")
    rating = -1
    try:
        table = soup.find_all('table', class_='dl-table')[1]
        th = table.contents[1].contents[0]
        td = table.contents[1].contents[1]
        # 非アクティブユーザー
        if (th.text == 'Rating'):
            rating = int(td.text)
        else:
            rating = int(table.contents[3].contents[1].text)
    except:
        # 削除済
        pass
    user = (d['user_id'], d['count'], rating)
    res.append(user)
    print('done {0} users...'.format(len(res)))

# AC数ランキング上位者のレーティング
for i, user in enumerate(res):
    name, count, rating = user
    print(i+1, name, count, rating)

# レート順
res.sort(key=itemgetter(2), reverse=1)
for i, user in enumerate(res):
    name, count, rating = user
    print(i+1, name, count, rating)

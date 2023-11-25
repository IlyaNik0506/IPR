import requests
from bs4 import BeautifulSoup as BS

r = requests.get('https://www.scrapethissite.com/pages/simple/')
html = BS(r.content, 'html.parser')

for i in html.select('.col-md-4.country'):
    title = i.select('.country-name')
    if title:
        country_name = title[0].text.strip()
    title1 = i.select('.country-info')
    if title1:
        capital_element = title1[0].select_one('.country-capital')
        if capital_element:
            capital = capital_element.text.strip()
    title2 = i.select('.country-info')
    if title2:
        population_element = title2[0].select_one('.country-population')
        if population_element:
            population = population_element.text.strip()
    title3 = i.select('.country-info')
    if title3:
        area_element = title3[0].select_one('.country-area')
        if area_element:
            area = area_element.text.strip()
    print(f'Страна: {country_name}, Столица: {capital}, Население: {population} человек, Площадь: {area} км2 \n')

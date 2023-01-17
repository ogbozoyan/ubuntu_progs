#!/usr/bin/python3
# -*- coding: utf-8 -*-

from fastapi import FastAPI, HTTPException, Response 
import uvicorn
from typing import * 
from fastapi.responses import JSONResponse
from pydantic import BaseModel
from fastapi.encoders import jsonable_encoder


app = FastAPI()
b_works = {"pilgrims": "Мимо ристалищ,\nкапищ,мимо храмов и баров,мимо шикарных кладбищ,\nмимо больших базаров,\nмира и горя мимо,\nмимо Мекки и Рима,\nсиним солнцем палимы,\nидут по земле пилигримы.",
           "letter": "Сохрани мою тень. Не могу объяснить. Извини.\nЭто нужно теперь. Сохрани мою тень, сохрани.\n"}
mayakovsky_works = {"cloud": "Вашу мысль,\nмечтающую на размягченном мозгу,\nкак выжиревший лакей на засаленной кушетке,\nбуду дразнить об окровавленный сердца лоскут:\nдосыта изъиздеваюсь, нахальный и едкий.\nУ меня в душе ни одного седого волоса,\nи старческой нежности нет в ней!\nМир огромив мощью голоса,\nиду — красивый,\nдвадцатидвухлетний.",
                    "voice": "Уважаемые товарищи потомки!\nРоясь в сегодняшнем окаменевшем г….,\nнаших дней изучая потёмки,\nвы, возможно, спросите и обо мне.\nИ, возможно, скажет ваш учёный,\nкроя эрудицией вопросов рой,\nчто жил-де такой певец кипячёной\nи ярый враг воды сырой.\n"}
mandelstam_works = {"leningrad": "Я вернулся в мой город, знакомый до слез,\nДо прожилок, до детских припухлых желез.\nТы вернулся сюда, — так глотай же скорей\nРыбий жир ленинградских речных фонарей.\nУзнавай же скорее декабрьский денек,\nГде к зловещему дегтю подмешан желток.\nПетербург, я еще не хочу умирать:\nУ тебя телефонов моих номера.\n"}

works = {"brodsky": b_works, 
         "mayakovsky": mayakovsky_works,
         "mandelstam": mandelstam_works
        }

class Items():

    def dir_init(self, dir_items: list):
        self.items = dir_items
        self.mode = "dir"
    
    def file_init(self, file_data: str, file_name: str):
        self.data = file_data
        self.name = file_name
        self.mode = "reg"



@app.get("/index", tags=["Главная"])
def index():
    return "Добро пожаловать в цифровую библиотеку"

@app.get("/library", tags=["Список авторов"])
def library():
    item = Items()
    item.dir_init(list(works.keys()))
    json_compatible_item_data = jsonable_encoder(item)
    return JSONResponse(content=json_compatible_item_data)

@app.get("/library/{author}", tags=["Список произведений автора"])
def library(author: str):
    lst=[]
    item = Items()
    for key in works.keys():
        if author == key:
            [lst.append(i) for i in works[key].keys()]
            item.dir_init(lst)
            json_compatible_item_data = jsonable_encoder(item)
            return JSONResponse(content=json_compatible_item_data)
    raise HTTPException(status_code = 404, detail = "Author not found")

@app.get("/library/{author}/{work}", tags=["Произведения"])
def library(author: str, work: str, begin: int = None, end:int = None):
    item = Items()
    for key in works.keys():
        if author == key:
            for title in works[key].keys():
                if title == work:
                    item.file_init(works[key][title][begin:end], f"{work}.txt")
                    json_compatible_item_data = jsonable_encoder(item)
                    return JSONResponse(content=json_compatible_item_data)
    raise HTTPException(status_code = 404, detail = "Work not found")



if __name__ == "__main__":
    uvicorn.run(app)

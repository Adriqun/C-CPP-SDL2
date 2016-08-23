#!/usr/bin/python

from engine import Engine

engine = Engine()

if engine.load():
	engine.loop()

engine.quit()
quit()



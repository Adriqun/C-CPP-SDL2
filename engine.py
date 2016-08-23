#!/usr/bin/python

import pygame
from core import Core
from texture import Texture

class Engine:

	def __init__( self ):
		self.core = Core( 60, 1024, 768, "Ninja" )

	def load( self ):
		success = True
		return success

	
	def handle( self ):
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				self.core.setQuit()	
	def loop( self ):
		while not self.core.isQuit():
			self.handle()
			self.core.fillDisplay()

			self.core.tickClock()
			pygame.display.update()
			
	def quit( self ):
		pygame.quit()
		







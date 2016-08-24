#!/usr/bin/python

import pygame
from texture import Texture

class Menucursor:
	
	def __init__( self ):
		self.cursor = Texture( "menu/cursor.png", 0, True )
		self.angle = 0
		self.x = 0
		self.y = 0
	
	def draw( self, screen ):
		self.angle += 1
		if self.angle > 360:
			self.angle = 0
		self.cursor.rotation( self.angle )
		
		self.cursor.setX( self.x - self.cursor.getWidth()*2/3 +10 )
		self.cursor.setY( self.y - self.cursor.getHeight()*2/3 +10 )		

		self.cursor.draw( screen)

	def handle( self, event ):
		self.x, self.y = pygame.mouse.get_pos()

		








		

#!/usr/bin/python

import pygame
from text import Text
from texture import Texture

class Menu_log:

#-------------------------------------------------------------------------------------------------------

	def __init__( self ):
		self.text = Text( "menu/KGHAPPY.ttf", 27, 255 )
		self.texture = Texture( 0, 255 )
		self.type = 0

#-------------------------------------------------------------------------------------------------------
	
	def load( self, width, height ):

		self.texture.load( "menu/exit.png" )
		self.texture.setX( width/2 - self.texture.getWidth()/2 )
		self.texture.setY( height/2 - self.texture.getHeight()/2 )
		self.texture.setColor( 30, 0, 255 )

		self.text.createText( "m-menu  b-back", [ 0xFF, 0xFF, 0xFF ] )
		self.text.setX( width/2 - self.text.getWidth()/2 )
		self.text.setY( height/2 - self.text.getHeight()/2 )

#-------------------------------------------------------------------------------------------------------
	
	def draw( self, window ):
		if self.type == 1:
			self.texture.draw( window )
			self.text.draw( window )

#-------------------------------------------------------------------------------------------------------

	def getState( self ):
		return self.type

#-------------------------------------------------------------------------------------------------------

	def setState( self, t ):
		self.type = t

#-------------------------------------------------------------------------------------------------------

	def handle( self, event ):

		if event.type == pygame.KEYDOWN:

			if event.key == pygame.K_m:
				if self.type == 0:
					self.type = 1
				elif self.type == 1:
					self.type = 2

			elif event.key == pygame.K_b:
				if self.type == 1:
					self.type = 0

#-------------------------------------------------------------------------------------------------------

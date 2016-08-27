#!/usr/bin/python

import pygame
from text import Text
from texture import Texture

class Menu_play_button:

#-------------------------------------------------------------------------------------------------------

	def __init__( self ):
		self.text = Text( "menu/KGHAPPY.ttf", 80 )
		self.texture = Texture( 4 )
		self.click = pygame.mixer.Sound( "menu/click.wav" )

		self.next = 0
		self.on = 0
		self.mouseup = 0

#-------------------------------------------------------------------------------------------------------
	
	def load( self, width, height ):

		self.text.createText( "play", [ 0x82, 0xae, 0x20 ] )
		self.text.setX( width/2 - self.text.getWidth()/2 )
		self.text.setY( height/2 - self.text.getHeight()/2 -10 +120 )
		
		self.texture.load( "menu/blankbutton.png" )
		self.texture.setX( width/2 - self.texture.getWidth()/2 )
		self.texture.setY( height/2 - self.texture.getHeight()/2 +120 )

#-------------------------------------------------------------------------------------------------------
	
	def draw( self, window ):
		self.texture.draw( window )
		self.text.draw( window )

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):
		self.texture.fadein( i, m )
		self.text.fadein( i, m )

#-------------------------------------------------------------------------------------------------------

	def fadeout( self, i = 1, m = 0 ):
		self.texture.fadeout( i, m )
		self.text.fadeout( i, m )

#-------------------------------------------------------------------------------------------------------

	def setState( self ):
		if self.on == 0:
			self.on = 1
		else:
			self.on = 0
		#print self.on

#-------------------------------------------------------------------------------------------------------
	
	def handle( self, event ):
		
		self.focus = False
		if event.type == pygame.MOUSEBUTTONDOWN:
			self.focus = True
			self.mouseup = 1
		elif event.type == pygame.MOUSEBUTTONUP:
			self.mouseup = 0
			
		
		self.texture.setOffset( 0 )
		self.x, self.y = pygame.mouse.get_pos()

		if self.x > self.texture.getLeft() and self.x < self.texture.getRight() and self.texture.getAlpha() == 255:
			if self.y > self.texture.getTop() and self.y < self.texture.getBot():
				if self.focus == True:
					if self.on == 0:
						self.click.play()
					self.next = 1

				if self.focus == True or self.mouseup == 1:
					self.texture.setOffset( 2 )
				else:
					self.texture.setOffset( 1 )

#-------------------------------------------------------------------------------------------------------

	def getAlpha( self ):
		return self.texture.getAlpha()

#-------------------------------------------------------------------------------------------------------

	def getState( self ):
		return self.next

#-------------------------------------------------------------------------------------------------------

	def getLeft( self ):
		return self.texture.getLeft()

#-------------------------------------------------------------------------------------------------------

	def getBot( self ):
		return self.texture.getBot()

#-------------------------------------------------------------------------------------------------------
		

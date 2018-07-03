#!/usr/bin/python

import pygame
from text import Text
from sprite import Sprite

class Menu_play_button:

#-------------------------------------------------------------------------------------------------------

	def __init__( self ):
		self.text = Text( "menu/KGHAPPY.ttf", 80 )
		self.sprite = Sprite( "menu/blankbutton.png", 4 )
		self.click = pygame.mixer.Sound( "menu/click.wav" )

		self.next = 0
		self.on = 0
		self.mouseup = 0

#-------------------------------------------------------------------------------------------------------
	
	def load( self, width, height ):

		self.text.createText( "play", [ 0x82, 0xae, 0x20 ] )
		self.text.setX( width/2 - self.text.getWidth()/2 )
		self.text.setY( height/2 - self.text.getHeight()/2 -10 +120 )

		self.sprite.setX( width/2 - self.sprite.getWidth()/2 )
		self.sprite.setY( height/2 - self.sprite.getHeight()/2 +120 )

#-------------------------------------------------------------------------------------------------------
	
	def draw( self, window ):
		self.sprite.draw( window )
		self.text.draw( window )

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):
		self.sprite.fadein( i, m )
		self.text.fadein( i, m )

#-------------------------------------------------------------------------------------------------------

	def fadeout( self, i = 1, m = 0 ):
		self.sprite.fadeout( i, m )
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
			
		
		self.sprite.setOffset( 0 )
		self.x, self.y = pygame.mouse.get_pos()

		if self.x > self.sprite.getLeft() and self.x < self.sprite.getRight() and self.sprite.getAlpha() == 255:
			if self.y > self.sprite.getTop() and self.y < self.sprite.getBot():
				if self.focus == True:
					if self.on == 0:
						self.click.play()
					self.next = 1

				if self.focus == True or self.mouseup == 1:
					self.sprite.setOffset( 2 )
				else:
					self.sprite.setOffset( 1 )

#-------------------------------------------------------------------------------------------------------

	def getAlpha( self ):
		return self.sprite.getAlpha()

#-------------------------------------------------------------------------------------------------------

	def getState( self ):
		return self.next

#-------------------------------------------------------------------------------------------------------

	def setNext( self, n ):
		self.next = n

#-------------------------------------------------------------------------------------------------------

	def getLeft( self ):
		return self.sprite.getLeft()

#-------------------------------------------------------------------------------------------------------

	def getBot( self ):
		return self.sprite.getBot()

#-------------------------------------------------------------------------------------------------------
		

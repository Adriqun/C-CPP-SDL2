#!/usr/bin/python

import pygame
import webbrowser
from sprite import Sprite

class Menu_link_button:

#-------------------------------------------------------------------------------------------------------

	def __init__( self, path, url, locked = False ):

		self.sprite = Sprite( path, 4 )
		self.url = url
		self.locked = locked

		if locked == True:
			self.sprite.setOffset( 3 )

		self.click = pygame.mixer.Sound( "menu/click.wav" )
		self.on = 0

#-------------------------------------------------------------------------------------------------------
	
	def load( self, width, y, flag = False ):

		if flag:
			self.sprite.setX( width )
		else:	
			self.sprite.setX( width - self.sprite.getWidth() -10 )

		self.sprite.setY( y )

#-------------------------------------------------------------------------------------------------------

	def getBot( self ):
		return self.sprite.getBot()

#-------------------------------------------------------------------------------------------------------
	
	def draw( self, window ):
		self.sprite.draw( window )

#-------------------------------------------------------------------------------------------------------

	def getRight( self ):
		return self.sprite.getRight()

#-------------------------------------------------------------------------------------------------------

	def setState( self ):
		if self.on == 0:
			self.on = 1
		else:
			self.on = 0
		# print self.on

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):
		self.sprite.fadein( i, m )

#-------------------------------------------------------------------------------------------------------

	def fadeout( self, i = 1, m = 0 ):
		self.sprite.fadeout( i, m )

#-------------------------------------------------------------------------------------------------------
		
	def handle( self, event ):
			
		if self.locked == False and self.sprite.getAlpha() == 255:
			self.sprite.setOffset( 0 )
			self.focus = False

			if event.type == pygame.MOUSEBUTTONDOWN:
				self.focus = True
		
			self.x, self.y = pygame.mouse.get_pos()

			if self.x > self.sprite.getLeft() and self.x < self.sprite.getRight():
				if self.y > self.sprite.getTop() and self.y < self.sprite.getBot():

					if self.focus == True:
						if self.on == 0:
							self.click.play()
							# print "CLICK!"							
							
						self.sprite.setOffset( 2 )
						webbrowser.open_new_tab( self.url )
					else:
						self.sprite.setOffset( 1 )

#-------------------------------------------------------------------------------------------------------

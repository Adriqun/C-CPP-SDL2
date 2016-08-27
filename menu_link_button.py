#!/usr/bin/python

import pygame
import webbrowser
from texture import Texture

class Menu_link_button:

#-------------------------------------------------------------------------------------------------------

	def __init__( self, path, url, locked = False ):

		self.path = path
		self.texture = Texture( 4 )
		self.url = url
		self.locked = locked

		if locked == True:
			self.texture.setOffset( 3 )

		self.click = pygame.mixer.Sound( "menu/click.wav" )
		self.on = 0

#-------------------------------------------------------------------------------------------------------
	
	def load( self, width, y, flag = False ):

		self.texture.load( self.path )
		if flag:
			self.texture.setX( width )
		else:	
			self.texture.setX( width - self.texture.getWidth() -10 )

		self.texture.setY( y )

#-------------------------------------------------------------------------------------------------------

	def getBot( self ):
		return self.texture.getBot()

#-------------------------------------------------------------------------------------------------------
	
	def draw( self, window ):
		self.texture.draw( window )

#-------------------------------------------------------------------------------------------------------

	def getRight( self ):
		return self.texture.getRight()

#-------------------------------------------------------------------------------------------------------

	def setState( self ):
		if self.on == 0:
			self.on = 1
		else:
			self.on = 0
		# print self.on

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):
		self.texture.fadein( i, m )

#-------------------------------------------------------------------------------------------------------

	def fadeout( self, i = 1, m = 0 ):
		self.texture.fadeout( i, m )

#-------------------------------------------------------------------------------------------------------
		
	def handle( self, event ):
			
		if self.locked == False and self.texture.getAlpha() == 255:
			self.texture.setOffset( 0 )
			self.focus = False

			if event.type == pygame.MOUSEBUTTONDOWN:
				self.focus = True
		
			self.x, self.y = pygame.mouse.get_pos()

			if self.x > self.texture.getLeft() and self.x < self.texture.getRight():
				if self.y > self.texture.getTop() and self.y < self.texture.getBot():

					if self.focus == True:
						if self.on == 0:
							self.click.play()
							# print "CLICK!"							
							
						self.texture.setOffset( 2 )
						webbrowser.open_new_tab( self.url )
					else:
						self.texture.setOffset( 1 )

#-------------------------------------------------------------------------------------------------------

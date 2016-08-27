#!/usr/bin/python

import pygame
from text import Text
from texture import Texture

class Menu_title:

#-------------------------------------------------------------------------------------------------------

	def __init__( self ):
		self.texture =  Texture()
		self.text = Text( "menu/KGHAPPY.ttf", 80 )

#-------------------------------------------------------------------------------------------------------		
		
	def load( self, width ):
		
		self.texture.load( "menu/belt.png" )
		self.texture.setX( ( width / 2 ) - ( self.texture.getWidth() / 2 ) )
		self.texture.setY( 10 )

		self.text.createText( "Ninja", [ 0x7F, 0x99, 0x95 ] )
		self.text.setX( ( width / 2 ) - ( self.text.getWidth() / 2 ) )
		self.text.setY( 0 )

#-------------------------------------------------------------------------------------------------------

	def draw( self, window ):
		self.texture.draw( window )
		self.text.draw( window )

#-------------------------------------------------------------------------------------------------------
		
	def getBot( self ):
		return self.texture.getBot() # +150

#-------------------------------------------------------------------------------------------------------
	
	def fadein( self, i = 1, m = 255 ):
		self.texture.fadein( i, m )
		self.text.fadein( i, m )

#-------------------------------------------------------------------------------------------------------

	def fadeout( self, i = 1, m = 0 ):
		self.texture.fadeout( i, m )
		self.text.fadeout( i, m )

#-------------------------------------------------------------------------------------------------------

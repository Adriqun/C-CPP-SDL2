#!/usr/bin/python

import pygame
from font import Font
from texture import Texture

class Menutitle:
	
	def __init__( self ):
		self.the = Font( "menu/KGHAPPY.ttf", 80 )
		#self.title = Font( "menu/KGHAPPY.ttf", 100 )
		#self.crown = Texture( "menu/crown.png" )
		self.belt =  Texture( "menu/belt.png" )
		
	
	def load( self, width ):

		self.belt.setX( (width / 2) - (self.belt.getWidth() / 2) )
		self.belt.setY( 10 )

		#self.crown.setX( (width / 2) - (self.crown.getWidth() / 2) )
		#self.crown.setY( self.belt.getTop() - self.crown.getHeight() + 4 )
		
		self.the.createText( "Ninja", 0x7F, 0x99, 0x95 )
		self.the.setX( (width / 2) - (self.the.getWidth() / 2) )
		self.the.setY( 0 )
		
	def getBot( self ):
		return self.belt.getBot()
	
	def fade( self, vel = 1 ):
		self.belt.fade( vel )
		self.the.fade( vel )

	
	def draw( self, screen ):
		self.belt.draw( screen)
		#self.crown.draw( screen)
		self.the.draw( screen )
		#self.title.draw( screen)
		








		

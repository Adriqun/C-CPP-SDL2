#!/usr/bin/python

import pygame
from texture import Texture

class Wall:

#-------------------------------------------------------------------------------------------------------
	
	def __init__( self ):
		self.bg_one = Texture( "wall/14.png" )
		self.bg_two = Texture( "wall/14.png" )

#-------------------------------------------------------------------------------------------------------

	def load( self ):
		self.bg_two.setX( self.bg_two.getWidth() )
		

#-------------------------------------------------------------------------------------------------------
	
	def draw( self, window, move = True, vel = 2 ):

		if self.bg_one.getAlpha() == 255 and move:
			self.bg_one.setX( self.bg_one.getLeft() - vel )
			self.bg_two.setX( self.bg_two.getLeft() - vel )
		
			if self.bg_one.getLeft() <= -self.bg_one.getWidth():
				self.bg_one.setX( self.bg_one.getWidth() )
			elif self.bg_two.getLeft() <= -self.bg_two.getWidth():
				self.bg_two.setX( self.bg_two.getWidth() )
			
		
		self.bg_one.draw( window )
		self.bg_two.draw( window )

#-------------------------------------------------------------------------------------------------------

	def getAlpha( self ):
		return self.bg_two.getAlpha()

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):
		self.bg_one.fadein( i, m )
		self.bg_two.fadein( i, m )

#-------------------------------------------------------------------------------------------------------

	def fadeout( self, i = 1, m = 0 ):
		self.bg_one.fadeout( i, m )
		self.bg_two.fadeout( i, m )

#-------------------------------------------------------------------------------------------------------

#!/usr/bin/python

import pygame
from texture import Texture

class Wall:

#-------------------------------------------------------------------------------------------------------
	
	def __init__( self ):
		self.bg_one = Texture()
		self.bg_two = Texture()

#-------------------------------------------------------------------------------------------------------

	def load( self ):
		self.bg_one.load( "wall/14.png" )
		self.bg_two.load( "wall/14.png" )
		self.bg_two.setX( -self.bg_one.getWidth() )

#-------------------------------------------------------------------------------------------------------
	
	def draw( self, window, value = 0 ):
		
		if value == 1:	# L
			if self.bg_one.getLeft() == 0:
				self.bg_two.setX( -self.bg_two.getWidth() )
			elif self.bg_two.getLeft() == 0:
				self.bg_one.setX( -self.bg_one.getWidth() )

			self.bg_one.setX( self.bg_one.getLeft() + 1 )
			self.bg_two.setX( self.bg_two.getLeft() + 1 )

		elif value == 2: # R
			if self.bg_one.getLeft() == 0:
				self.bg_two.setX( self.bg_two.getWidth() )
			elif self.bg_two.getLeft() == 0:
				self.bg_one.setX( self.bg_one.getWidth() )

			self.bg_one.setX( self.bg_one.getLeft() - 1 )
			self.bg_two.setX( self.bg_two.getLeft() - 1 )

		
		self.bg_one.draw( window )
		self.bg_two.draw( window )

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):
		self.bg_one.fadein( i, m )
		self.bg_two.fadein( i, m )

#-------------------------------------------------------------------------------------------------------

	def fadeout( self, i = 1, m = 0 ):
		self.bg_one.fadeout( i, m )
		self.bg_two.fadeout( i, m )

#-------------------------------------------------------------------------------------------------------

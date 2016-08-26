#!/usr/bin/python

import pygame
from texture import Texture

class Wall:
	
	def __init__( self ):
		self.bg_one = Texture( "wall/14.png", 0, 254 )
		self.bg_two = Texture( "wall/14.png", 0, 254 )
		self.bg_two.setX( -self.bg_one.getWidth() )
	
	def draw( self, screen, value = 0 ):
		
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

		
		self.bg_one.draw( screen )
		self.bg_two.draw( screen )

	def fade( self, vel = 1 ):
		self.bg_one.fade( vel )
		self.bg_two.fade( vel )

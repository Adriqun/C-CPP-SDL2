#!/usr/bin/python

import pygame
from texture import Texture

'''
	0-3 MOVE
	4   IDLE
	5   JUMP
	6   ATTACK
	7   DEAD
'''

class Hero:

#-------------------------------------------------------------------------------------------------------
	
	def __init__( self ):

		self.hero = Texture( 8 )
		self.hero.setOffset( 4 )

		self.move = 8
		self.delay = 2
		self.startstate = 0
		self.stateD = False
		self.stateA = False
		self.stateSpace = False

#-------------------------------------------------------------------------------------------------------

	def load( self, width, height ):
		self.hero.load( "hero/0.png" )
		self.hero.setX( 0 )
		self.hero.setY( height - 130 - self.hero.getHeight() )

		self.minX = width/4
		self.maxX = width*4/5

#-------------------------------------------------------------------------------------------------------
	
	def draw( self, window, move = True ):
		
		if self.hero.getAlpha() == 255 and move:

			if self.startstate == 0:
				if self.hero.getX() < self.minX:
					self.hero.setX( self.hero.getX() + 3 )
				else:
					self.startstate = 1

			elif self.stateD and self.hero.getRight() < self.maxX:
				self.hero.setX( self.hero.getX() + 6 )
			elif self.hero.getRight() >= self.maxX:
				self.stateD = False

			if self.hero.getX() > self.minX +5:
				self.hero.setX( self.hero.getX() - 3 )
			if self.stateA and self.hero.getX() > self.minX +5:
				self.hero.setX( self.hero.getX() - 4 )


			self.move += 1
			if self.move >= 4 * self.delay:
				self.move = 0

		self.hero.setOffset( self.move / self.delay )
		self.hero.draw( window )

#-------------------------------------------------------------------------------------------------------

	def handle( self, event ):

		if self.startstate == 1:
			if event.type == pygame.KEYDOWN:
				if event.key == pygame.K_d:
					self.stateD = True
				elif event.key == pygame.K_a:
					self.stateA = True
			elif event.type == pygame.KEYUP:
				if event.key == pygame.K_d:
					self.stateD = False
				elif event.key == pygame.K_a:
					self.stateA = False
		
#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):
		self.hero.fadein( i, m )

#-------------------------------------------------------------------------------------------------------

	def fadeout( self, i = 1, m = 0 ):
		self.hero.fadeout( i, m )

#-------------------------------------------------------------------------------------------------------

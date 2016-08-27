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

		self.hero = Texture( "hero/0.png", 8, 1 )
		self.hero.setOffset( 4 )

		#STATES
		self.move = 0
		#self.jump = 0 # 1 - UP, 2 - DOWN
		#self.attack = False
		#self.dead = False


	def load( self, height ):
		self.hero.setX( 0 )
		self.hero.setY( height - 130 - self.hero.getHeight() )
	
	def draw( self, screen ):
		self.move += 1
		if self.move == 4:
			self.move = 0
		self.hero.setOffset( self.move )

		self.hero.draw( screen )



	def handle( self, event ):
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_SPACE:
				print "space"
		




	def fade( self, value = 1 ):
		self.hero.fade( value )





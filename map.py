#!/usr/bin/python

import pygame
from texture import Texture

class Map:

#-------------------------------------------------------------------------------------------------------
	
	def __init__( self ):
		self.texture = []
		self.x = [ [] ]
		self.nr = 10
		for i in range( 0, self.nr ):
			self.texture.append( Texture() )

#-------------------------------------------------------------------------------------------------------

	def load( self ):
		self.texture[ 0 ].load( "wall/1.png" )
		self.texture[ 1 ].load( "wall/5.png" ) 
		self.texture[ 2 ].load( "wall/6.png" ) 
		self.texture[ 3 ].load( "wall/7.png" ) 
		self.texture[ 4 ].load( "wall/8.png" ) 
		self.texture[ 5 ].load( "wall/9.png" ) 
		self.texture[ 6 ].load( "wall/10.png" ) 
		self.texture[ 7 ].load( "wall/11.png" ) 
		self.texture[ 8 ].load( "wall/12.png" ) 
		self.texture[ 9 ].load( "wall/13.png" ) 
		

#-------------------------------------------------------------------------------------------------------
	'''
	def draw( self, window, move = True, vel = 2 ):
		
		

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
	'''

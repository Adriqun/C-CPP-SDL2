#!/usr/bin/python

import pygame
from texture import Texture

class Map:

#-------------------------------------------------------------------------------------------------------
	
	def __init__( self ):
		self.texture = []
		self.x = []
		self.y = []

		self.nr = 14
		for i in range( 0, self.nr ):
			self.texture.append( Texture( "wall/" + str(i) + ".png" ) )
			self.x.append( [] )
			self.y.append( [] )

#-------------------------------------------------------------------------------------------------------

	def load( self, txt = 0 ):
		
		for i in range( 0, self.nr ):
			self.number = len( self.x[ i ] )
			for j in range( 0, self.number ):
				del self.x[ i ][ 0 ]
				del self.y[ i ][ 0 ]
			del self.number

		self.fo = open( "wall/" + str( txt ) + ".txt", "r" )

		self.t = 0
		self.x_t = 0
		self.y_t = 0
		self.line_t = ""
		
		for line in self.fo:	#File

			for i in range (0, len(line) ):	#Type
				if line[ i ] == '.':
					self.t = int( self.line_t )
					self.line_t = ""

					for j in range (i+1, len(line) ):	#Pos x
						if line[ j ] == '.':
							self.x_t = int( self.line_t )
							self.line_t = ""

							for k in range (j+1, len(line) ):	#Pos y
								if line[ k ] == '.':
									self.y_t = int( self.line_t )
									self.line_t = ""

									break
								self.line_t += line[ k ]
							break
						self.line_t += line[ j ]
					break
				self.line_t += line[ i ]

			# print self.t, self.x_t, self.y_t
			self.x[ self.t ].append( self.x_t )
			self.y[ self.t ].append( self.x_t )

		self.fo.close()
		del self.fo

		del self.t
		del self.x_t
		del self.y_t
		del self.line_t
		

#-------------------------------------------------------------------------------------------------------
	
	def draw( self, window ):
		for i in range( 0, self.nr ):
			for j in range( 0, len( self.x[ i ] ) ):
				self.texture[ i ].setX( self.x[ i ][ j ] )
				self.texture[ i ].setY( self.y[ i ][ j ] )
				self.texture[ i ].draw( window )
		

#-------------------------------------------------------------------------------------------------------

	def getAlpha( self ):
		return self.texture[ 6 ].getAlpha()

#-------------------------------------------------------------------------------------------------------

	def fadein( self, i = 1, m = 255 ):
		for k in range( 0, self.nr ):
			self.texture[ k ].fadein( i, m )

#-------------------------------------------------------------------------------------------------------

	def fadeout( self, i = 1, m = 0 ):
		for k in range( 0, self.nr ):
			self.texture[ k ].fadeout( i, m )

#-------------------------------------------------------------------------------------------------------

#!/usr/bin/python

import pygame
import os

class Core:

	def __init__( self, FPS, width, height, caption ):
		
		self.state = -1
		self.quit = False	#Main bool.
		self.FPS = FPS		#Frames per second.

		self.width = width	#Screen width
		self.height = height	#Screen height
		
		pygame.init()				#INIT PYGAME
		self.clock = pygame.time.Clock()	#Timer

		self.window = pygame.display.set_mode( ( width, height ) )	#Window
		pygame.display.set_caption( caption )				#Caption
		
		#Icon
		self.icon = pygame.image.load( "window/icon.bmp" )
		self.icon.set_colorkey( [ 0x00, 0xFF, 0x00 ] )
		pygame.display.set_icon( self.icon )
		

	def getWidth( self ):
		return self.width

	def getHeight( self ):
		return self.height

	def isQuit( self ):
		return self.quit

	def setQuit( self ):
		self.quit = True

	def fillDisplay( self ):
		self.window.fill( [ 0x15, 0x15, 0x1D ] )

	def tickClock( self ):
		self.clock.tick( self.FPS )

	def getWindow( self ):
		return self.window

	def getState( self ):
		return self.state

	def setState( self, state ):
		self.state = state

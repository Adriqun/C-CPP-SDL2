#!/usr/bin/python

import pygame
from texture import Texture

class Menubg:
	
	def __init__( self ):
		self.background = Texture( "menu/background.png" )
	
	def draw( self, screen ):
		self.background.draw( screen )
	
	def setAlpha( self, newalpha ):
		self.background.setAlpha( newalpha )

	def fade( self, vel = 1 ):
		self.background.fade( vel )

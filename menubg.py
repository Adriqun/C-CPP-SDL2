#!/usr/bin/python

import pygame
from texture import Texture

class Menubg:
	
	def __init__( self ):
		self.background = Texture( "menu/background.png" )
	
	def draw( self, screen ):
		self.background.draw( screen )

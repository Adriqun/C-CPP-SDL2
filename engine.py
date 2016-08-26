#!/usr/bin/python

import pygame
import pyaudio

from core import Core

from menubg import Menubg
from menutitle import Menutitle
from menuplay import Menuplay
from linkbutton import Linkbutton
from menumus import Menumus
from menubutton import Menubutton
from menuposition import Menuposition
from menuplaymusic import Menuplaymusic

from intro import Intro

from wall import Wall

class Engine:

	def __init__( self ):

		self.core = Core( 60, 1024, 768, "Ninja" )

		self.menubg = Menubg()
		self.menutitle = Menutitle()
		self.menuplay = Menuplay()

		self.menugit = Linkbutton( "menu/git.png", "https://github.com/Adriqun" )
		self.menugoogle = Linkbutton( "menu/google.png", "https://en.wikipedia.org/wiki/Ninja" )
		self.menufacebook = Linkbutton( "menu/facebook.png", "nothing", True )
		self.menutwitter = Linkbutton( "menu/twitter.png", "nothing", True )

		self.menumus = Menumus( "menu/music.png" )
		self.menuchunk = Menumus( "menu/chunk.png", 1 )

		self.author = Menubutton( "menu/author.png" )
		self.menugame = Linkbutton( "menu/game.png", "nothing", True )
		self.menusettings = Linkbutton( "menu/settings.png", "nothing", True )
		self.menuposition = Menuposition( "menu/position.png" )

		self.menuplaymusic = Menuplaymusic( "menu/Rayman Legends OST - Moving Ground.mp3" )

		self.intro = Intro()

		self.wall = Wall()

	def load( self ):
		self.menutitle.load( self.core.getW() )
		self.menuplay.load( self.core.getW(), self.core.getH() )
		self.menugit.load( self.core.getW(), 10 )
		self.menugoogle.load( self.core.getW(), self.menugit.getBot() )
		self.menufacebook.load( self.core.getW(), self.menugoogle.getBot() )
		self.menutwitter.load( self.core.getW(), self.menufacebook.getBot() )
		self.menumus.load( 10 )
		self.menuchunk.load( self.menumus.getBot() )
		#print self.core.getH()
		self.author.load( self.menuplay.getLeft()+5, self.core.getW(), self.menutitle.getBot(), self.menuplay.getBot() )
		self.menugame.load( self.author.getRight(), self.menuplay.getBot()+10, True )
		self.menusettings.load( self.menugame.getRight(), self.menuplay.getBot()+10, True )
		self.menuposition.load( self.menusettings.getRight(), self.core.getW(), self.menutitle.getBot(), self.menuplay.getBot() )
		
		self.intro.load( self.core.getW(), self.core.getH() )
		self.core.setState( 1 )
	
	def handle( self ):
		for event in pygame.event.get():

			if event.type == pygame.QUIT:
				self.core.setQuit()
			
			if self.core.getState() == 0:
				
				#HANDLE IF AUTHOR BUTTON == OFF AND POSITION BUTTON == OFF
				if self.author.getType() == 0 and self.menuposition.getType() == 0:
					self.menuplay.handle( event )
					self.menugit.handle( event )
					self.menugoogle.handle( event )
					self.menumus.handle( event )
					self.menuchunk.handle( event )
				if self.menuposition.getType() == 0:
					self.author.handle( event )
				if self.author.getType() == 0:
					self.menuposition.handle( event )

	def states( self ):
		
		#INTRO
		if self.core.getState() == -1:
			self.intro.draw( self.core.getWindow() )
			if self.intro.getQuit():
				self.core.setState( 0 )

		#MENU
		if self.core.getState() == 0:

			self.menuplaymusic.play()
			#FADE IN
			if self.menuplay.getNext() != 1:
				self.menubg.fade(5)
				self.menutitle.fade(5)
				self.menuplay.fade(5)
				self.menugit.fade(5)
				self.menugoogle.fade(5)
				self.menufacebook.fade(5)
				self.menutwitter.fade(5)
				self.menumus.fade(5)
				self.menuchunk.fade(5)
				self.author.fade(5)
				self.menugame.fade(5)
				self.menusettings.fade(5)
				self.menuposition.fade(5)
			
			#DRAW ALWAYS IN MENU STATE
			self.menubg.draw( self.core.getWindow() )
			self.menutitle.draw( self.core.getWindow() )

			#DRAW IF AUTHOR BUTTON == OFF AND POSITION BUTTON == OFF
			if self.author.getType() == 0 and self.menuposition.getType() == 0:
				self.menugit.draw( self.core.getWindow() )			
				self.menugoogle.draw( self.core.getWindow() )
				self.menufacebook.draw( self.core.getWindow() )
				self.menutwitter.draw( self.core.getWindow() )
				self.menuplay.draw( self.core.getWindow() )
				self.menumus.draw( self.core.getWindow() )
				self.menuchunk.draw( self.core.getWindow() )
				self.menugame.draw( self.core.getWindow() )
				self.menusettings.draw( self.core.getWindow() )
			
			if self.menuposition.getType() == 0:
				self.author.draw( self.core.getWindow() )
			if self.author.getType() == 0:
				self.menuposition.draw( self.core.getWindow() )
			
			#IF USER TURN ON/OFF CHUNKS
			if self.menuchunk.getState():
				self.menugit.setState()		#GIT
				self.menugoogle.setState()	#GOOGLE
				#self.menufacebook.setState()	#FACEBOOK - locked
				#self.menutwitter.setState()	#TWITTER - locked
				self.menuplay.setState()	#PLAY BUTTON
				self.menumus.setState()		#MUSIC BUTTON
				self.menuchunk.setState()	#CHUNK BUTTON
				self.author.setState()		#AUTHOR BUTTON
				self.menuposition.setState()	#POSITION BUTTON

			#IF USER TURN ON/OFF MUSIC
			if self.menumus.getState():
				self.menuplaymusic.pause()
			
			#IF USER CLICK PLAY BUTTON
			if self.menuplay.getNext() == 1:
				self.menubg.fade(-6)
				self.menutitle.fade(-6)
				self.menuplay.fade(-6)
				self.menugit.fade(-6)
				self.menugoogle.fade(-6)
				self.menufacebook.fade(-6)
				self.menutwitter.fade(-6)
				self.menumus.fade(-6)
				self.menuchunk.fade(-6)
				self.author.fade(-6)
				self.menugame.fade(-6)
				self.menusettings.fade(-6)
				self.menuposition.fade(-6)
				self.menuplaymusic.fadeOut()

				if self.menuplay.getAlpha() < 2:
					self.menuplaymusic.stop()
					self.core.setState( 1 )

		elif self.core.getState() == 1:

			#FADE IN
			self.wall.fade( 5 )
			self.wall.draw( self.core.getWindow() )	



















	def loop( self ):
		while not self.core.isQuit():
			self.handle()
			self.core.fillDisplay()
			self.states()
			self.core.tickClock()
			pygame.display.update()
			
	def quit( self ):
		pygame.quit()
		







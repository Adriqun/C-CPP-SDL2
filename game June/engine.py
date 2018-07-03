#!/usr/bin/python

import pygame
import pyaudio

from core import Core

from intro import Intro

from texture import Texture
from menu_title import Menu_title
from menu_play_button import Menu_play_button
from menu_link_button import Menu_link_button
from menu_music_button import Menu_music_button
from menu_exit_log import Menu_exit_log
from menu_author_log import Menu_author_log
from menu_score_log import Menu_score_log
from menu_music import Menu_music

from wall import Wall
from hero import Hero
from menu_log import Menu_log
from map import Map


class Engine:

#-------------------------------------------------------------------------------------------------------
	def __init__( self ):

		self.core = Core( 60, 1024, 768, "Ninja" )

		self.intro = Intro()

		self.menu_background = Texture( "menu/background.png" )
		self.menu_title = Menu_title()
		self.menu_play_button = Menu_play_button()
		self.menu_git_button = Menu_link_button( "menu/git.png", "https://github.com/Adriqun" )
		self.menu_google_button = Menu_link_button( "menu/google.png", "https://en.wikipedia.org/wiki/Ninja" )
		self.menu_facebook_button = Menu_link_button( "menu/facebook.png", "nothing", True )
		self.menu_twitter_button = Menu_link_button( "menu/twitter.png", "nothing", True )
		self.menu_music_button = Menu_music_button( "menu/music.png" )
		self.menu_chunk_button = Menu_music_button( "menu/chunk.png", 1 )
		self.menu_exit_log = Menu_exit_log()
		self.menu_author_log = Menu_author_log()
		self.menu_game_log = Menu_link_button( "menu/game.png", "nothing", True )
		self.menu_settings_log = Menu_link_button( "menu/settings.png", "nothing", True )
		self.menu_score_log = Menu_score_log()
		self.menu_music = Menu_music( "menu/Rayman Legends OST - Moving Ground.mp3" )
		
		self.wall = Wall()
		self.hero = Hero()
		self.menu_log = Menu_log()
		self.map = Map()
	
#-------------------------------------------------------------------------------------------------------

	def load( self ):

		self.core.setState( -1 )

		self.intro.load( self.core.getWidth(), self.core.getHeight() )

		self.menu_title.load( self.core.getWidth() )
		self.menu_play_button.load( self.core.getWidth(), self.core.getHeight() )
		self.menu_git_button.load( self.core.getWidth(), 10 )
		self.menu_google_button.load( self.core.getWidth(), self.menu_git_button.getBot() )
		self.menu_facebook_button.load( self.core.getWidth(), self.menu_google_button.getBot() )
		self.menu_twitter_button.load( self.core.getWidth(), self.menu_facebook_button.getBot() )
		self.menu_music_button.load( 10 )
		self.menu_chunk_button.load( self.menu_music_button.getBot() )
		self.menu_exit_log.load( self.core.getWidth(), self.core.getHeight() )
		self.menu_author_log.load( self.menu_play_button.getLeft()+5, self.core.getWidth(), self.menu_title.getBot() +150, self.menu_play_button.getBot() )
		self.menu_game_log.load( self.menu_author_log.getRight(), self.menu_play_button.getBot() +10, True )
		self.menu_settings_log.load( self.menu_game_log.getRight(), self.menu_play_button.getBot() +10, True )
		self.menu_score_log.load( self.menu_settings_log.getRight(), self.core.getWidth(), self.menu_title.getBot() +150, self.menu_play_button.getBot() )

		self.wall.load()
		self.hero.load( self.core.getWidth(), self.core.getHeight() )
		self.menu_log.load( self.core.getWidth(), self.core.getHeight() )
		self.map.load()

#-------------------------------------------------------------------------------------------------------	

	def handle( self ):
		for event in pygame.event.get():

			if event.type == pygame.QUIT:
				self.core.setQuit()

#-------------------------------------------------------------------------------------------------------

			if self.core.getState() == 0:
				
				if self.menu_play_button.getState() == 0:
					self.menu_exit_log.handle( event )

				#HANDLE IF AUTHOR BUTTON == OFF AND SCORE BUTTON == OFF
				if self.menu_author_log.getState() == 0 and self.menu_score_log.getState() == 0:
					self.menu_play_button.handle( event )
					self.menu_git_button.handle( event )
					self.menu_google_button.handle( event )
					self.menu_music_button.handle( event )
					self.menu_chunk_button.handle( event )
				if self.menu_score_log.getState() == 0:
					self.menu_author_log.handle( event )
				if self.menu_author_log.getState() == 0:
					self.menu_score_log.handle( event )

#-------------------------------------------------------------------------------------------------------

			if self.core.getState() == 1:
				
				self.menu_log.handle( event )
				#HANDLE IF MENU_LOG == OFF
				if self.menu_log.getState() == 0:
					self.hero.handle( event )
				
#-------------------------------------------------------------------------------------------------------

	def states( self ):

#-------------------------------------------------------------------------------------------------------STATE -1

		if self.core.getState() == -1:
			self.intro.draw( self.core.getWindow() )
			if self.intro.getQuit():
				self.intro.free()
				del self.intro
				self.menu_music.play()#MENU MUSIC
				self.core.setState( 0 )
		

#-------------------------------------------------------------------------------------------------------STATE 0

		if self.core.getState() == 0:

			#FADE IN
			if self.menu_play_button.getState() != 1 and self.menu_exit_log.getState() == 0:
				self.menu_background.fadein( 5 )
				self.menu_title.fadein( 5 )
				self.menu_play_button.fadein( 5 )
				self.menu_git_button.fadein( 5 )
				self.menu_google_button.fadein( 5 )
				self.menu_facebook_button.fadein( 5 )
				self.menu_twitter_button.fadein( 5 )
				self.menu_music_button.fadein( 5 )
				self.menu_chunk_button.fadein( 5 )
				self.menu_author_log.fadein( 5 )
				self.menu_game_log.fadein( 5 )
				self.menu_settings_log.fadein( 5 )
				self.menu_score_log.fadein( 5 )
				self.menu_music.setVolume( 1.0 )

			#DRAW ALWAYS IN MENU STATE
			self.menu_background.draw( self.core.getWindow() )
			self.menu_title.draw( self.core.getWindow() )
			self.menu_exit_log.draw( self.core.getWindow() )
			#DRAW IF AUTHOR BUTTON == OFF AND SCORE BUTTON == OFF
			if self.menu_author_log.getState() == 0 and self.menu_score_log.getState() == 0:
				self.menu_git_button.draw( self.core.getWindow() )			
				self.menu_google_button.draw( self.core.getWindow() )
				self.menu_facebook_button.draw( self.core.getWindow() )
				self.menu_twitter_button.draw( self.core.getWindow() )
				self.menu_play_button.draw( self.core.getWindow() )
				self.menu_music_button.draw( self.core.getWindow() )
				self.menu_chunk_button.draw( self.core.getWindow() )
				self.menu_game_log.draw( self.core.getWindow() )
				self.menu_settings_log.draw( self.core.getWindow() )

			if self.menu_score_log.getState() == 0:
				self.menu_author_log.draw( self.core.getWindow() )
			if self.menu_author_log.getState() == 0:
				self.menu_score_log.draw( self.core.getWindow() )

			#IF USER TURN ON/OFF CHUNKS
			if self.menu_chunk_button.getState():
				self.menu_play_button.setState()
				self.menu_git_button.setState()
				self.menu_google_button.setState()
				self.menu_music_button.setState()
				self.menu_chunk_button.setState()
				self.menu_author_log.setState()
				self.menu_score_log.setState()
			#IF USER TURN ON/OFF MUSIC
			if self.menu_music_button.getState():
				self.menu_music.pause()

			#IF USER PRESS Q - EXIT
			if self.menu_exit_log.getState() == 1:
				self.menu_background.fadeout( 6, 120 )
				self.menu_title.fadeout( 6, 120 )
				self.menu_play_button.fadeout( 6, 120 )
				self.menu_git_button.fadeout( 6, 120 )
				self.menu_google_button.fadeout( 6, 120 )
				self.menu_facebook_button.fadeout( 6, 120 )
				self.menu_twitter_button.fadeout( 6, 120 )
				self.menu_music_button.fadeout( 6, 120 )
				self.menu_chunk_button.fadeout( 6, 120 )
				self.menu_author_log.fadeout( 6, 120 )
				self.menu_game_log.fadeout( 6, 120 )
				self.menu_settings_log.fadeout( 6, 120 )
				self.menu_score_log.fadeout( 6, 120 )
				self.menu_music.setVolume( 0.3 )

			elif self.menu_exit_log.getState() == 2:
				self.menu_background.fadeout( 6 )
				self.menu_title.fadeout( 6 )
				self.menu_play_button.fadeout( 6 )
				self.menu_git_button.fadeout( 6 )
				self.menu_google_button.fadeout( 6 )
				self.menu_facebook_button.fadeout( 6 )
				self.menu_twitter_button.fadeout( 6 )
				self.menu_music_button.fadeout( 6 )
				self.menu_chunk_button.fadeout( 6 )
				self.menu_author_log.fadeout( 6 )
				self.menu_game_log.fadeout( 6 )
				self.menu_settings_log.fadeout( 6 )
				self.menu_score_log.fadeout( 6 )
			if self.menu_exit_log.getState() == 2 and self.menu_background.getAlpha() == 0:
				self.core.setQuit()

			#IF USER CLICK PLAY BUTTON
			if self.menu_play_button.getState() == 1:
				self.menu_background.fadeout( 6 )
				self.menu_title.fadeout( 6 )
				self.menu_play_button.fadeout( 6 )
				self.menu_git_button.fadeout( 6 )
				self.menu_google_button.fadeout( 6 )
				self.menu_facebook_button.fadeout( 6 )
				self.menu_twitter_button.fadeout( 6 )
				self.menu_music_button.fadeout( 6 )
				self.menu_chunk_button.fadeout( 6 )
				self.menu_author_log.fadeout( 6 )
				self.menu_game_log.fadeout( 6 )
				self.menu_settings_log.fadeout( 6 )
				self.menu_score_log.fadeout( 6 )
				if self.menu_music.isPaused() == False:
					self.menu_music.fadeOut()

				if self.menu_play_button.getAlpha() == 0:
					self.menu_play_button.setNext( 0 )
					self.core.setState( 1 )

#-------------------------------------------------------------------------------------------------------STATE 1
		
		if self.core.getState() == 1:
			
			#FADE IN IF PAUSE BUTTON == OFF AND MENU_LOG == OFF
			if self.menu_log.getState() == 0:
				self.wall.fadein( 5 )
				self.hero.fadein( 5 )
				self.map.fadein( 5 )
			elif self.menu_log.getState() == 1:
				self.wall.fadeout( 6, 130 )
				self.hero.fadeout( 6, 130 )
				self.map.fadeout( 6, 130 )
			elif self.menu_log.getState() == 2:
				self.wall.fadeout( 6 )
				self.hero.fadeout( 6 )
				self.map.fadeout( 6 )
				if self.wall.getAlpha() == 0:
					self.menu_log.setState( 0 )
					if self.menu_music.isPaused() == False:
						self.menu_music.play()
					self.core.setState( 0 ) #Back to menu
			
			#DRAW
			self.wall.draw( self.core.getWindow() )
			self.hero.draw( self.core.getWindow() )
			self.menu_log.draw( self.core.getWindow() )
			self.map.draw( self.core.getWindow() )














	def loop( self ):
		while not self.core.isQuit():
			self.handle()
			self.core.fillDisplay()
			self.states()
			self.core.tickClock()
			pygame.display.update()
			
	def quit( self ):
		pygame.quit()
		







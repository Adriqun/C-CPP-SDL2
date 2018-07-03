#!/usr/bin/python

import pygame
import time

pygame.init()

FPS = 30
screen_width = 800
screen_height = 600

white = (0xFF, 0xFF, 0xFF)
black = (0, 0, 0)
red = (0xFF, 0, 0)

gameDisplay = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption('Slither')

clock = pygame.time.Clock()

font = pygame.font.SysFont(None, 25)
def message_to_screen(msg, color):
	screen_text = font.render(msg, True, color)
	gameDisplay.blit(screen_text, [screen_width/2, screen_height/2])

def gameLoop():
	quit = False;
	gameover = False;

	lead_x = screen_width/2
	lead_y = screen_height/2
	block_size = 10

	lead_x_change = 0
	lead_y_change = 0

	while not quit:
		
		while quit == True:
			gameDisplay.fill(white)
			message_to_screen("Game over, press c to play again, q to quit")
			pygame.display.update()

			for event in pygame.event.get():
				if event.type = pygame.KEYDOWN:
					if event.key == pygame.K_q
								

		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				quit = True
			if event.type == pygame.KEYDOWN:
				if event.key == pygame.K_LEFT:
					lead_x_change = -block_size
					lead_y_change = 0;
				elif event.key == pygame.K_RIGHT:
					lead_x_change = block_size
					lead_y_change = 0;
				elif event.key == pygame.K_UP:
					lead_y_change = -block_size
					lead_x_change = 0;
				elif event.key == pygame.K_DOWN:
					lead_y_change = block_size
					lead_x_change = 0;

			if lead_x >= screen_width or lead_x < 0 or lead_y >= screen_height or lead_y < 0:
				quit = True
		
			'''
			if event.type == pygame.KEYUP:
				if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
					lead_x_change = 0
			'''
				

		lead_x += lead_x_change
		lead_y += lead_y_change

		gameDisplay.fill(white)
		pygame.draw.rect( gameDisplay, black, [lead_x, lead_y, block_size, block_size])

		clock.tick(FPS)

		pygame.display.update()

	message_to_screen("You suck", red)
	pygame.display.update()
	time.sleep(2)
	pygame.quit()
	quit()

gameLoop()

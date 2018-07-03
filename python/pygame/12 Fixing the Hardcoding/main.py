#!/usr/bin/python

import pygame

pygame.init()

FPS = 30
screen_width = 800
screen_height = 600

gameDisplay = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption('Slither')

quit = False;

lead_x = screen_width/2
lead_y = screen_height/2
block_size = 10

lead_x_change = 0
lead_y_change = 0

clock = pygame.time.Clock()


while not quit:
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

	gameDisplay.fill([0xFF, 0xFF, 0xFF])
	pygame.draw.rect( gameDisplay, [0, 0, 0], [lead_x, lead_y, block_size, block_size])

	clock.tick(FPS)

	pygame.display.update()

pygame.quit()

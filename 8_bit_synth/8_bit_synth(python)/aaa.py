import pygame

fps = 30
pygame.mixer.init(fps, -16, 1, 512) # 太灵活了 ;)
screen = pygame.display.set_mode((640,480)) # 设置焦点

# 得到键盘的键位的正确顺序的列表
# ``keys`` 如 ['Q','W','E','R' ...] 一样排列
keys = open('typewriter.kb').read().split('\n')

sounds = map(pygame.sndarray.make_sound, transposed)
key_sound = dict( zip(keys, sounds) )
is_playing = {k: False for k in keys}

while True:

    event =  pygame.event.wait()

    if event.type in (pygame.KEYDOWN, pygame.KEYUP):
        key = pygame.key.name(event.key)

    if event.type == pygame.KEYDOWN:

        if (key in key_sound.keys()) and (not is_playing[key]):
            key_sound[key].play(fade_ms=50)
            is_playing[key] = True

        elif event.key == pygame.K_ESCAPE:
            pygame.quit()
            raise KeyboardInterrupt

    elif event.type == pygame.KEYUP and key in key_sound.keys():

        key_sound[key].fadeout(50) # 停止播放并50ms淡出
        is_playing[key] = False

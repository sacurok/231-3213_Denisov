import random, string, datetime, os

import faker
from faker import Faker
fk = Faker()

from django.db import transaction
from django.contrib.auth.models import Group, User
from .models import *

def gentestdata():

    with transaction.atomic():
        for i in range(1000):
            newMusicAlbum = MusicAlbum()
            authors = [fk.name() for _ in range(10)]
            
            newMusicAlbum.name = fk.catch_phrase()
            newMusicAlbum.author = random.choice(authors)
            newMusicAlbum.release_date = fk.date_between(
                start_date=datetime.date(1960,1,1),
                end_date=datetime.date(2025,1,1))
            newMusicAlbum.genre = random.choice(('Rock', 'Pop', 'Electronic', 'Hip-Hop'))
            newMusicAlbum.songs_quantitty = random.randint(1, 20)

            newMusicAlbum.save()
    print('OK gentestdata()')

def cleartestdata():
    MusicAlbum.objects.all().delete()

if __name__=='__main__':
    gentestdata()
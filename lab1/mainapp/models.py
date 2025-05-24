from django.db import models

# Create your models here.

class MusicAlbum(models.Model):
    name = models.CharField(max_length=64, null=True)
    author = models.CharField(max_length=32, null=True)
    release_date = models.DateField(null=True)
    genre = models.CharField(max_length=16, null=True)
    songs_quantitty = models.SmallIntegerField(null=True)

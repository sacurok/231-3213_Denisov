from django.shortcuts import render

from django.conf import settings

import rest_framework
from rest_framework import viewsets

from .models import MusicAlbum
from .serializers import AlbumSerializer

class AlbumViewSet(viewsets.ModelViewSet):
    queryset = MusicAlbum.objects.all()
    serializer_class = AlbumSerializer
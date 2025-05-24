from rest_framework import serializers

from .models import MusicAlbum

class AlbumSerializer(serializers.ModelSerializer):

    class Meta:
        model = MusicAlbum
        fields = '__all__'
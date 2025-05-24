"""
URL configuration for lab1 project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/5.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, include

from django.conf import settings
from django.conf.urls.static import static

from rest_framework import routers

from mainapp.views import AlbumViewSet

urlpatterns = [
    path('admin/', admin.site.urls),
    path('api/',
        include([
            path('album.get', AlbumViewSet.as_view({'get': 'list'})),
            path('album.get/<pk>', AlbumViewSet.as_view({'get': 'retrieve'})),
            path('album.create', AlbumViewSet.as_view({'post': 'create'})),
            path('album.delete/<pk>', AlbumViewSet.as_view({'get': 'destroy'})),
            path('album.update/<pk>', AlbumViewSet.as_view({'post': 'update'})),
        ])
        
    )
]

urlpatterns += static(settings.STATIC_URL, document_root=settings.STATIC_ROOT)
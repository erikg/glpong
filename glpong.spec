Summary: OpenGL Pong.
Name: glpong
Version: 1.0
Release: 1
Copyright: GPL
Vendor: Erik Greenwald
Url: http://math.smsu.edu/~erik/software.php?id=72
Group: Amusements/Games
Source0: http://math.smsu.edu/~erik/files/glpong-1.0.tar.gz
Buildroot: /usr/src/redhat/BUILD/glpong

%description
An implementation of the classic game 'Pong' using OpenGL, SDL, SDL_image, and
SDL_mixer. The only mode of play is one player against an AI. 

%prep
%setup -q
%build
CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=/usr

make

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/bin
mkdir -p $RPM_BUILD_ROOT/usr/share/glpong
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
/usr/bin/glpong
/usr/share/glpong/*

%changelog


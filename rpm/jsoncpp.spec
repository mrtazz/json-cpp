Name:		jsoncpp
Version:	0.6.0
Release:	1%{?dist}
Summary:	MakerBot branch of library for reading and writing JSON for C++

License:	GPL
URL:		http://github.com/makerbot/json-cpp
Source:	        %{name}-%{version}.tar.gz

BuildRequires:	gcc


%description
jsoncpp is an implementation of a JSON reader and writer in C++. This is
the MakerBot branch of the tree; when Fedora carries this library in their main repository, MakerWare will be retargeted to use the default jsoncpp


%prep
%setup -q -n json-cpp


%build
scons install_prefix=%{buildroot}/%{_prefix} config_prefix=%{buildroot}/%{_sysconfdir}


%install
rm -rf %{build_root}
scons install_prefix=%{buildroot}/%{_prefix} config_prefix=%{buildroot}/%{_sysconfdir} install


%files
/usr/lib/lib*.so


%package devel
Summary:	Developent files for MakerBot json-cpp

%description devel
jsoncpp is an implementation of a JSON reader and writer in C++. This is
the development files for the MakerBot branch of the tree; when Fedora carries this library in their main repository, MakerWare will be retargeted to use the default jsoncpp

%files devel
%{_includedir}/%{name}/json/*.h


%changelog


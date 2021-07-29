FROM ruby

RUN apt-get -y update && apt-get -y upgrade
RUN apt-get install -y nodejs
RUN gem update && gem install bundler && gem install rails

ONBUILD COPY . /opt/app

ONBUILD WORKDIR /opt/app

ONBUILD RUN bundle install && rails db:migrate && rails db:seed
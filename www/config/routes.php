<?php 
return array(
  'token/([A-Za-z0-9]+)/(\w+@[a-zA-Z_]+?\.[a-zA-Z]{2,3})' => 'token/$1/$2',
  'login/([a-z]+)' => 'user/login/$1',
  'login' => 'user/login',
  'post/([A-Za-z][A-Za-z0-9]+)/([0-9]+)' => 'post/$1/$2',
  'post/([A-Za-z0-9]+)' => 'post/$1',
  'action/([A-Za-z0-9]+)' => 'action/$1',
  'post' => 'home/index',
  '' => 'home/index',
);
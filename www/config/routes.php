<?php 
return array(
  'login/([a-z]+)' => 'user/login/$1',
  'login' => 'user/login',
  'post/([A-Za-z][A-Za-z0-9]+)/([0-9]+)' => 'post/$1/$2',
  'post/([A-Za-z0-9]+)' => 'post/$1',
  'post' => 'home/index',
  '' => 'home/index',
);
<?php 
return array(
  '([A-Za-z][A-Za-z0-9]+)/([0-9]+)' => 'post/$1/$2',
  '([A-Za-z0-9]+)' => 'post/$1',
  '' => 'home/index',
);
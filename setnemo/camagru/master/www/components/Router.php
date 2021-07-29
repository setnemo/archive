<?php

class Router {
  
  private $routes;
  
  /**
  * Get routes with create new Obj Router
  */
  public function __construct() {
    $routesPath = ROOT.'/config/routes.php';
    $this->routes = include($routesPath);
  }
  
  /**
  * Get URI, return string
  */
  public function getURI() {
    if (!empty($_SERVER['REQUEST_URI'])) {
      return trim($_SERVER['REQUEST_URI'], '/');
    }
  }
  
  public function run() {
    $uri = $this->getURI();
    $result = array();
    foreach ($this->routes as $uriPattern => $path) {
      if (preg_match("~$uriPattern~", $uri)) {
        $internalRoute = preg_replace("~$uriPattern~", $path, $uri);
        $actionName = 'actionIndex';
        $controllerName = 'PostController';
        $controllerFile = ROOT . '/controllers/' . $controllerName . '.php';
        $segments = explode('/', $internalRoute);
        if (count($segments) == 2 || count($segments) == 3) {
          // echo "<pre>";
          // echo " print_r(segments);";
          // print_r($segments);
          // echo "</pre>";
          $controllerName = array_shift($segments) . 'Controller';
          $controllerName = ucfirst($controllerName);
          if (count($segments) == 2) {
              $actionName = "actionExternal";
            }
          $controllerFile = ROOT . '/controllers/' . $controllerName . '.php';
          // echo "0x00\t" . $controllerFile . "<br>";
          // echo "0x01\t" . $controllerName . "<br>";
          // echo "<pre>";
          // echo "before:<br>";
          // print_r($segments);
          // echo "</pre>";
        } else {
          $actionName = 'action404';
        };
          // echo "0x02\t" . $actionName . "<br>";
        if (file_exists($controllerFile)) {
            include_once($controllerFile);
          $controllerObject = new $controllerName;
          $result = call_user_func_array(array($controllerObject, $actionName), $segments);
        }
        if ($result != null) {
            break;
        }
      }
    }
//     if (count($result) == 0) {
      // echo "Not found<br>";
//     }
  }
}
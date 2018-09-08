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
        $segments = explode('/', $internalRoute);
//         echo "<pre>test".count($segments)."<br>";
//         print_r($segments);
//         echo "</pre>";
        if (count($segments) == 2) { $actionName = 'actionIndex'; } else if (count($segments) == 3) {$actionName = 'actionViewUser';} else {$actionName = 'action404';};
        $controllerName = array_shift($segments) . 'Controller';
        $controllerName = ucfirst($controllerName);
        $parameters = $segments;
        $controllerFile = ROOT . '/controllers/' . $controllerName . '.php';
        $controllerFile = ROOT . '/controllers/' . $controllerName . '.php';
//         echo "0x00\t" . $controllerFile . "<br>";
//         echo "0x01\t" . $controllerName . "<br>";
//         echo "0x02\t" . $actionName . "<br>";
        if (file_exists($controllerFile)) {
//           echo "privet" . $controllerFile . PHP_EOL;
            include_once($controllerFile);
//           echo "<pre>";
//           echo "before:<br>";
//           print_r($parameters);
//           echo "</pre>";
          $controllerObject = new $controllerName;
          $result = call_user_func_array(array($controllerObject, $actionName), $parameters);
        }
        if ($result != null) {
            break;
        }
      }
    }
//     if (count($result) == 0) {
//       echo "Not found<br>";
//     }
  }
}
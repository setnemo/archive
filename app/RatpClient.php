<?php

class RatpClient {

    private $urlBase = 'api.navitia.io/v1/';

    private $coverage = 'fr-idf';

    private $token = 'fd1abb9a-aef3-421c-8da4-e1a78c490af9:';

    private function getMatrix(array $routes) {
        $matrix = array();
        foreach ($routes as $routename => $route) {
            foreach ($route as $key) {
                $matrix[$key['label']][] = $routename;
            }
        }
        return $matrix;
    }
    
    private function get_next_station(string $label, string $line, array $routes) {
        $stop = 0;
        foreach ($routes[$line] as $station) {
            if ($stop == 0 && $station['label'] !== $label) {
                continue ;
            }
            $stop++;
            if ($stop == 2) {
                return $station['label'];
            }

        }
        return 'null';
    }
    private function getMap(array $routes) {
        $matrix = array();
        foreach ($routes as $routename => $route) {
            foreach ($route as $key) {
                $matrix[$key['label']][$routename] = array('next' => $this->get_next_station($key['label'], $routename, $routes), 'dist' => -42);
            }
        }
        return $matrix;
    }

    public function getMetro(string $userInput) {
        $q = 'places?q=' . $userInput . '&type[stoppoint]=address';
        $ret = $this->performQuery($q);
        return $this->getMetroPointNearbyPlace($ret);
    }

    public function getTest() {
        $q = 'networks/network%3AOIF%3A439/routes?depth=3&';
        $data = $this->performQuery($q);
    }

    private function lastNotFound(array $queue, string $last, array &$map)
    {
        foreach ($queue as $key => $line) {
            $map[$line['next']][$key]['dist'] = 1;
            if ($line['next'] === $last)
                return false;
        }
        return true;
    } 
    public function getJourney(array $routes, string $first, string $last) {
        $stop = 0;
        $matrix = $this->getMatrix($routes);
        $map = $this->getMap($routes);
        $journey1 = array();
        $queue = array();
        $queue = $map[$first];
        foreach ($map[$first] as &$key) {
            $key['dist'] = 0;
        }
        $iterat = $this->lastNotFound($queue, $last, $map);
        // while ($iterat)
        // {

        // }
        return $queue;
    }

    public function getRoutes() {
        $q = 'networks/network%3AOIF%3A439/routes?depth=3&';
        $routes = $this->performQuery($q)['routes'];
        $myroutes = array();
        foreach ($routes as $route) {
           foreach ($route['stop_points'] as $stoppoint) {
            $myroutes[$route['id']][] = array('label' => $stoppoint['stop_area']['label'], 'id' => $stoppoint['id']);
           }
        }
        return $myroutes;
    }

    public function getMetroPointNearbyPlace($data) {
        $coords = array();
        $temp = $data['places'];
        for ($i=0; $i < sizeof($temp); $i++) {
            if ($temp[$i]['embedded_type'] === 'stop_area' ) {
                $flag = 0;
                if (isset($temp[$i]['stop_area']['commercial_modes']))
                {
                    for ($j=0; $j < sizeof($temp[$i]['stop_area']['commercial_modes']); $j++) { 
                            if ($temp[$i]['stop_area']['commercial_modes'][$j]['id'] == 'commercial_mode:metro'){
                                $flag = 1;
                            }
                    }
                }
                if ($flag != 0) {
                    $coords[] = array('name' => $temp[$i]['stop_area']['name'], 'id' => $temp[$i]['stop_area']['id']);
                }
            }
        }
        return $coords;
    }

    public function performQuery(string $url)
    {
        $q = $this->getQuery($url);
        $ch = curl_init(); 
        curl_setopt($ch, CURLOPT_URL, $q);
        curl_setopt($ch, CURLOPT_USERPWD, $this->token);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        $result = curl_exec($ch);
        curl_close($ch);

        return json_decode($result, true);
    }

    public function getQuery($url) {
        $base = 'https://' . $this->urlBase . 'coverage/' . $this->coverage . '/';
        return  $base . $url;
    }
}

<?php

class RatpClient {

    private $urlBase = 'api.navitia.io/v1/';
    private $coverage = 'fr-idf';
    private $token = 'fd1abb9a-aef3-421c-8da4-e1a78c490af9:';
    private $network = 'network%3AOIF%3A439';
    
    public function getMetro(string $userInput) {
        $q = 'places?q=' . $userInput . '&type[stoppoint]=address';
        $ret = $this->performQuery($q);
        return $this->getMetroPointNearbyPlace($ret);
    }

    public function getRoutes() {
        $q = 'networks/' . $this->network . '/routes?depth=3&';
        $routes = $this->performQuery($q)['routes'];
        $myroutes = array();
        foreach ($routes as $route) {
           foreach ($route['stop_points'] as $stoppoint) {
            $myroutes[$route['id']][] = array('label' => $stoppoint['stop_area']['label'], 'id' => $stoppoint['id']);
           }
        }
        return $myroutes;
    }

    public function getMetroPointNearbyPlace(array $data) {
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
                    $coords[] = array('label' => $temp[$i]['stop_area']['label'], 'id' => $temp[$i]['stop_area']['id']);
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

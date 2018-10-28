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
    private function getArrayFromJson($data) {
        $json_array = json_decode($data, true);
        $assoc_array = array();
        for($i = 0; $i < sizeof($json_array); $i++)
        {
             $key = $json_array[$i]['name'];
             $assoc_array[$key] = $json_array[$i]['value'];
        }
        return $json_array;
    }

    public function getMetro(string $userInput) {
        $q = 'places?q=' . $userInput . '&type[stoppoint]=address';
        $ret = $this->performQuery($q);
        return $this->getMetroPointNearbyPlace($ret);
    }

    public function getTest(string $userInput) {
        $q = '' . $userInput;
        $data = $this->performQuery($q);
        return $this->getArrayFromJson($data);
    }

    public function getJourney(array $routes, string $first, string $last) {
        $stop = 0;
        // $firstline = '';
        // $firstline_r = '';
        // foreach ($routes as $routename => $route) {
        //     foreach ($route as $key) {
        //         if ($key['id'] === $first) {
        //             $stop++;
        //             if ($stop === 1)
        //                 $firstline = $routename;
        //             else
        //                 $firstline_r = $routename;
        //             break ;
        //         }
        //     }
        //     if ($stop === 2)
        //         break ;
        // }
        // echo '<br> firstline => ' . $firstline .'<br>' . '<br>firstline_r =>  ' . $firstline_r .'<br>';
        $matrix = $this->getMatrix($routes);
        $journey1 = array();
        $queue = array();
        $queueSt = array();
        // while ($stop)
        // {
        //     $queue = $matrix[$first];
        //     foreach ($queue as $name => $line) {
        //         foreach ($routes[$name] as $key) {
        //             if (in_array($last, $key))
        //                 $stop = 0;
        //         }
        //     }
        //     if ($stop) {
        //         foreach ($queue as $name => $line) {
        //             foreach ($routes[$name] as $key) {
        //                 if
        //             }
        //         }
        //     }
        // }

        $queue = $matrix[$first];
        foreach ($queue as $name => $line) {
            $flag = 0;
            foreach ($routes[$line] as $key) {
                if ($flag === 0 && $key['label'] !== $first) {
                   echo $key['label'];
                   continue ;
                }
                $flag++;
                if ($flag === 2) {
                    echo "HERAK!";
                    $queue = array_unique(array_merge($matrix[$key['label']], $queue));
                    // break ;
                }
            }
        }
        return $queue;
    }

    public function getRoutes(array $routes) {
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
        $temp = $this->getArrayFromJson($data)['places'];
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
                    // $coords[] = array('name' => $temp[$i]['stop_area']], 'id' => $temp[$i]['stop_area']['id']); //show alls data in stop_area
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

        // return json_decode($result, true);
        return $result;
    }

    public function getQuery($url) {
        $base = 'https://' . $this->urlBase . 'coverage/' . $this->coverage . '/';
        // echo $base . $url;
        return  $base . $url;
    }
}

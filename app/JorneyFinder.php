<?php

class JourneyFinder {

    public function bfs(array $root, $first, $goal)
    {
        $open = new SplQueue();
        $closed = new SplQueue();

        $open->enqueue($first);
        $way = [];
        $it = 0;
        $jt = 0;
        $check = 0;
        while (!$open->isEmpty()) {
            $now = $open->dequeue();
            $now = $root[$now];
            $way[$now['name']] = $now;
            $check = 0;
            if (isset($way[$now['name']]['links'])) {
                $check = count($way[$now['name']]['links']);
                foreach ($way[$now['name']]['links'] as &$key) {
                    $key['dist'] = $jt;
                    // echo $key['dist']."<br>";
                }
            }
            if ($now['name'] == $goal['name']) {
                return $way;
            }
            if (isset($now['links']))
            {
                foreach ($now['links'] as $value) {
                    if (in_array($value['next'], iterator_to_array($closed))) {
                        continue;
                    }
                    if (!in_array($value['next'], iterator_to_array($open))) {
                        $open->enqueue($value['next']);
                    }
                }
            }
            if ($it == $check) {
                $it = 0;
                $jt++;
            } else { $it++;}
            $closed->enqueue($now['name']);
        }
    }

    public function getJourney(array $routes, string $first, string $last)
    {
        $stop = 0;
        $matrix = $this->getMatrix($routes);
        $map = $this->getMap2($routes);
        $journey1 = array();
        $queue = array();
        // foreach ($map[$first] as &$key) {
        //     $key['dist'] = 0;
        // }
        // $iterat = $this->lastNotFound($queue, $last, $map);
        // $queue = $map[$first];
        $test = $this->bfs($map, $first, $map[$last]);
        $iterator = 1;
        $new = array();
        while (true)
        {
            foreach ($test as $value) {
                if (isset($value['links'])) {
                    foreach ($value['links'] as $key) {
                       $new[$key['routename']][] = $value['name'];
                        // echo $key['next'];
                    }
                }
            }
            break ;
        }
        $result = array();
        foreach ($new as $key) {
            if (in_array($first, $key)) {
                $result['first'] = $key;
                break ;
            }
        }
        foreach ($new as $key) {
            if (in_array($last, $key)) {
                $result['last'] = $key;
                break ;
            }
        }
        $result['first'] = array_reverse ($result['first']);
        $result['last'] = array_reverse ($result['last']);
        $result2 = array();
        foreach ($result['last'] as $key) {
            $result2['result'][] = $key;
            if (in_array($key, $result['first'])){
                foreach ($result['first'] as $key2) {
                    if ($stop == 0 && $key2 != $key) {
                        continue;
                    }
                    $stop++;
                    if ($stop > 1) {
                        $result2['result'][] = $key2;
                    }
                }
                break ;
            }
        }
        return  $result2 ;
        // return $map;
    }

    private function getMatrix(array $routes) {
        $matrix = array();
        foreach ($routes as $routename => $route) {
            foreach ($route as $key) {
                $matrix[$key['label']][] = $routename;
            }
        }
        return $matrix;
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

    private function getMap2(array $routes) {
        $matrix = array();
        foreach ($routes as $routename => $route) {
            foreach ($route as $key) {
                if ($this->get_next_station($key['label'], $routename, $routes) !== 'null') {
                $matrix[$key['label']] = 
                array( 'name' => $key['label'],
                );
                }
            }
        }
        foreach ($routes as $routename => $route) {
            foreach ($route as $key) {
                if ($this->get_next_station($key['label'], $routename, $routes) !== 'null') {
                $matrix[$key['label']]['links'][] = array('routename' => $routename, 'next' => $this->get_next_station($key['label'], $routename, $routes), 'dist' => -42);
                }
            }
        }
        return $matrix;
    }
    private function getMap(array $routes) {
        $matrix = array();
        foreach ($routes as $routename => $route) {
            foreach ($route as $key) {
                if ($this->get_next_station($key['label'], $routename, $routes) !== 'null') {
                $matrix[$key['label']][$routename] = array('next' => $this->get_next_station($key['label'], $routename, $routes), 'dist' => -42);
                }
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
}
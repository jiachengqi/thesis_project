package com.example.server;

import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface ServerRepo extends CrudRepository<Server, Integer> {
    List<Server> findById(int id);
}
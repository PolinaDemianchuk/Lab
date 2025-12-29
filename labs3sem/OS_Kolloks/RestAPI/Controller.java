package com.rest.crud;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@RestController
@RequestMapping("/tasks")
public class Controller
{
    private final List<Task> taskList = new ArrayList<>();
    private long counter = 0;

    @GetMapping
    public List<Task> getAllTasks()
    {
        return taskList;
    }

    @PostMapping
    public ResponseEntity<Task> createTask(@RequestBody Task task)
    {
        counter++;
        task.setId(counter);
        if (task.getStatus() == null)
        {
            task.setStatus("todo");
        }
        taskList.add(task);
        return new ResponseEntity<>(task, HttpStatus.CREATED);
    }

    @GetMapping("/{id}")
    public ResponseEntity<Task> getTaskById(@PathVariable Long id)
    {
        for (Task task : taskList)
        {
            if (task.getId().equals(id))
            {
                return ResponseEntity.ok(task);
            }
        }
        return ResponseEntity.notFound().build();
    }

    @PutMapping("/{id}")
    public ResponseEntity<Task> updateTask(@PathVariable Long id, @RequestBody Task taskDetails) {
        for (Task task : taskList)
        {
            if (task.getId().equals(id))
            {
                task.setTitle(taskDetails.getTitle());
                task.setDescription(taskDetails.getDescription());
                task.setStatus(taskDetails.getStatus());
                return ResponseEntity.ok(task);
            }
        }
        return ResponseEntity.notFound().build();
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteTask(@PathVariable Long id)
    {
        for (int i = 0; i < taskList.size(); i++)
        {
            if (taskList.get(i).getId().equals(id))
            {
                taskList.remove(i);
                return ResponseEntity.noContent().build();
            }
        }
        return ResponseEntity.notFound().build();
    }

}
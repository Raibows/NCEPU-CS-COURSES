package com.example.backstage.Entity.WebSearchEntity;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;
import org.springframework.format.annotation.DateTimeFormat;

import javax.persistence.*;
import java.util.Date;

@Data
@Entity
@Table(name = "comment")
public class Comment {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;
    private String content;
    @JsonFormat(pattern = "yyyy-MM-dd")
    private Date publishDate;
    private String studentName;
    private String major;
    private boolean pass;

    public Comment(String content, Date publishDate, String studentName, String major, boolean pass) {
        this.content = content;
        this.publishDate = publishDate;
        this.studentName = studentName;
        this.major = major;
        this.pass = pass;
    }

    public Comment() {
    }
}

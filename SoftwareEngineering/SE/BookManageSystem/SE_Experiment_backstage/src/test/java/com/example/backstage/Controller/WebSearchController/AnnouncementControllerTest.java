package com.example.backstage.Controller.WebSearchController;

import com.alibaba.fastjson.JSONObject;
import com.example.backstage.Entity.WebSearchEntity.Announcement;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After; 
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

import java.util.Date;

/** 
* AnnouncementController Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class AnnouncementControllerTest {
    @Autowired
    private MockMvc mvc;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: queryAllAnn(@RequestBody JSONObject object) 
* 
*/ 
@Test
public void testQueryAllAnn() throws Exception { 
//TODO: Test goes here...
    String str="{\"page\":0,\"size\":10}";
    mvc.perform(MockMvcRequestBuilders.post("/search/queryAllAnn")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(str)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: addAnn(@RequestBody Announcement ann) 
* 
*/ 
@Test
public void testAddAnn() throws Exception { 
//TODO: Test goes here...
    Announcement ann=new Announcement("单元测试","junit测试",0,new Date(),new Date()
    ,"我");
    String json= JSONObject.toJSONString(ann);
    mvc.perform(MockMvcRequestBuilders.post("/search/addAnn")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: deleteAnn(@RequestBody Announcement ann) 
* 
*/ 
@Test
public void testDeleteAnn() throws Exception { 
//TODO: Test goes here...
    Announcement ann=new Announcement();
    ann.setId(8);
    String json= JSONObject.toJSONString(ann);
    mvc.perform(MockMvcRequestBuilders.post("/search/deleteAnn")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: updateAnn(@RequestBody Announcement ann) 
* 
*/ 
@Test
public void testUpdateAnn() throws Exception { 
//TODO: Test goes here...
    Announcement ann=new Announcement("单元测试","junit测试",0,new Date(),new Date()
            ,"我");
    ann.setId(5);
    String json= JSONObject.toJSONString(ann);
    mvc.perform(MockMvcRequestBuilders.post("/search/updateAnn")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 

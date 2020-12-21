package com.example.test.controller;

import com.alibaba.fastjson.JSONObject;
import com.example.test.ResultVO;
import com.example.test.bean.JournalBean;
import com.example.test.bean.JournalSubscribeInfo;
import com.example.test.service.JournalService;
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@CrossOrigin
@Controller
public class JournalController {

    @Autowired
    private JournalService journalService;

    @RequestMapping(value = "/search_journal",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @CrossOrigin
    public ResultVO getJournalInfo(@RequestBody(required = true)JSONObject jsonObject ){

        int pageNum = Integer.parseInt( jsonObject.getString("pageNum"));
        int pageSize = Integer.parseInt(jsonObject.getString("pageSize"));

        PageHelper.startPage(pageNum,pageSize);

        List<JournalBean> journalBeans = journalService.SearchJournal(jsonObject.getString("period"));
        PageInfo<JournalBean> journalBeanPageInfos = new PageInfo<JournalBean>(journalBeans);
        PageHelper.clearPage();
        return ResultVO.SUCCESS( journalBeanPageInfos ) ;
    }

    @RequestMapping(value = "/add_journal",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    public ResultVO addJournal(@RequestBody(required = true) JournalBean journalBean){
        System.out.println("SQL语句前："+journalBean.getNo());
        journalService.AddJournal(journalBean.getNo(),
                journalBean.getJournalName(),
                journalBean.getStartYear(),
                journalBean.getPeriod(),
                journalBean.getDescription());
        System.out.println("SQL语句后："+journalBean.getNo());
        return ResultVO.SUCCESS("增添成功！");
    }

    @RequestMapping(value = "/delete_journal",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    public ResultVO deleteJournal(@RequestBody(required = true) JournalBean journalBean){
        journalService.DeleteJournal(journalBean.getNo());
        return ResultVO.SUCCESS("删除成功！");
    }



    @RequestMapping(value = "/modify_journal",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @CrossOrigin
    public ResultVO modifyJournalDescription(@RequestBody(required = true) JournalBean journalBean){
        journalService.ModifyJournal(journalBean.getNo(),journalBean.getDescription(),journalBean.getPeriod());
        return ResultVO.SUCCESS("修改期刊信息成功!");
    }

    @RequestMapping(value = "/subscribe_journal",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @CrossOrigin
    public ResultVO subscribeJournal(@RequestBody(required = true)JournalSubscribeInfo journalSubscribeInfo){
        journalService.JournalSubscibe(journalSubscribeInfo.getJournalNo(),
                journalSubscribeInfo.getStuId(),
                journalSubscribeInfo.getJournalName(),
                journalSubscribeInfo.getPeriod(),
                journalSubscribeInfo.getDescription());
        return ResultVO.SUCCESS("订阅成功!");
    }

    @RequestMapping(value = "/cancel_subscribe",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @CrossOrigin
    public ResultVO cancelSubscribe(@RequestBody(required = true) JSONObject jsonObject){
        journalService.JournalCancel(jsonObject.getString("journalNo"),jsonObject.getString("stuId"));
        return ResultVO.SUCCESS("取消订阅成功!");
    }

    @RequestMapping(value = "/search_subscribe",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @CrossOrigin
    public ResultVO searchSubscribe(@RequestBody(required = true) JSONObject jsonObject){

        int pageNum = Integer.parseInt( jsonObject.getString("pageNum"));
        int pageSize = Integer.parseInt(jsonObject.getString("pageSize"));

        PageHelper.startPage(pageNum,pageSize);

        List<JournalSubscribeInfo> journalSubscribeInfos = journalService.SearchSubscribe(jsonObject.getString("stuId"));
        PageInfo<JournalSubscribeInfo> journalSubscribePageInfos = new PageInfo<JournalSubscribeInfo>(journalSubscribeInfos);
        PageHelper.clearPage();
        return ResultVO.SUCCESS( journalSubscribePageInfos ) ;
    }



}

package com.example.test.controller;


import com.alibaba.fastjson.JSONObject;
import com.example.test.ResultVO;
import com.example.test.bean.BorrowInfo;
import com.example.test.service.BorrowInfoService;
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.stereotype.Controller;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.*;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;


@Controller
@Slf4j
@CrossOrigin
public class BorrowController {

    SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");

    @Autowired
    BorrowInfoService borrowInfoService;

    @RequestMapping("/borrowbook")
    public String show(){
        return "search_borrow";
    }

    /**
     *
     * @param jsonObject
     * @return
     */
    @RequestMapping(value = "/search_borrow",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    public ResultVO getBorrowInfoByID(@RequestBody(required = true) JSONObject jsonObject )  {

        int pageNum = Integer.parseInt(jsonObject.getString("pageNum"));
        int pageSize = Integer.parseInt(jsonObject.getString("pageSize"));

        PageHelper.startPage(pageNum,pageSize);
        List <BorrowInfo> borrowInfos = borrowInfoService.getBorrowInfo_By_ID(jsonObject.getString("stuid"));
        PageInfo<BorrowInfo> pageInfos = new PageInfo<BorrowInfo>(borrowInfos);
        PageHelper.clearPage();
        return ResultVO.SUCCESS(pageInfos);
    }

    /**
     *
     * @param jsonObject
     * @return
     */
    @RequestMapping(value = "/search_unreturn",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    public ResultVO getUnreturnInfoByID(@RequestBody(required = true) JSONObject jsonObject )  {

        int pageNum = Integer.parseInt(jsonObject.getString("pageNum"));
        int pageSize = Integer.parseInt(jsonObject.getString("pageSize"));

        PageHelper.startPage(pageNum,pageSize);
        List <BorrowInfo> borrowInfos = borrowInfoService.getUnreturnInfo_By_ID(jsonObject.getString("stuid"));
        PageInfo<BorrowInfo> pageInfos = new PageInfo<BorrowInfo>(borrowInfos);
        PageHelper.clearPage();
        return ResultVO.SUCCESS(pageInfos);
    }


    /**
     * *
     * @param borrowInfo
     * @return
     */
    @RequestMapping(value = "/borrow_book",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @Transactional
    @ApiOperation("根据 学号 ISBN 借书")
    @ApiImplicitParam(name="borrowInfo",value = "借书信息",required = true)
    public ResultVO borrowABook(@RequestBody(required = true) BorrowInfo borrowInfo ) throws ParseException {
        String ISBN = borrowInfo.getIsbn();
        String StuID = borrowInfo.getStuid();
        if(borrowInfoService.ReviewBookCondition(ISBN) == 0 ){
            return ResultVO.SUCCESS("该书籍已被借出！");
        }else{
            if (borrowInfoService.ReviewBorrConditon(StuID) == 0 ){
                return ResultVO.SUCCESS("您当前可借书籍达到最大！");
            }else {
                Date date = new Date();
                borrowInfoService.BorrowBook(StuID,ISBN,date);
                borrowInfoService.SetBorrowedBook(ISBN);
                borrowInfoService.SetBorrowedStudent(StuID);
                return ResultVO.SUCCESS("借书成功！");
            }
        }
    }

    @RequestMapping(value = "/return_book",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @Transactional
    @ApiOperation("根据 学号 ISBN 还书")
    @ApiImplicitParam(name="borrowInfo",value = "借书信息",required = true)
    public ResultVO returnABook(@RequestBody(required = true) BorrowInfo borrowInfo ){
        String ISBN = borrowInfo.getIsbn();
        String StuID = borrowInfo.getStuid();
        if (borrowInfoService.ReviewReturnStatus(StuID,ISBN) == 0 ){
            System.out.println(StuID);
            System.out.println(ISBN);
            return ResultVO.SUCCESS("书目不可归还");
        }
        Date date = new Date();
        borrowInfoService.ReturnBook(StuID,ISBN,date);
        borrowInfoService.ReturnStatus(StuID,ISBN);
        borrowInfoService.SetReturnedBook(ISBN);
        borrowInfoService.SetReturnedStudent(StuID);
        if (borrowInfoService.overdue(StuID,ISBN) == 0 ){
            return ResultVO.SUCCESS("归还成功！");
        }
        int days = borrowInfoService.getOverdueDays(StuID,ISBN);
        double penalty = borrowInfoService.SetPenalty(days,StuID);
        System.out.println(penalty);
        return ResultVO.SUCCESS(days);

    }


}
